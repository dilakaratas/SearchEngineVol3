#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "bst.h"
#include "hashtable.h"
#include "quicksort.h"
#include "insertionsort.h"
#include "mergesort.h"
#include "heapsort.h"

using namespace std;

#pragma comment(linker, "/STACK:6000000") // for the space

struct DocumentItem {
    string documentName;
    int count;
    DocumentItem* next;
    DocumentItem(const string& name, int c) : documentName(name), count(c), next(nullptr) {}
};

class WordItem {
public:
    WordItem() {}

    string word;
    DocumentItem* documents;
    WordItem(const string& w) : word(w) {
        documents = nullptr;
    }

    void Update(WordItem* item) {
        if (documents == nullptr) {
            documents = new DocumentItem(item->documents->documentName, 1);
            return;
        }
        DocumentItem* iterator = documents;
        while (true) {
            if (iterator->documentName == item->documents->documentName) {
                iterator->count++;
                return;
            }
            if (iterator->next == nullptr) break; // check if there is no next document
            iterator = iterator->next; // next iterator
        }
        iterator->next = new DocumentItem(item->documents->documentName, 1);
    }
};

bool operator<(const DocumentItem& left, const DocumentItem& right) {
    return left.documentName < right.documentName;
}

bool operator<(const WordItem& left, const WordItem& right) {
    return left.word < right.word;
}

bool operator>(const DocumentItem& left, const DocumentItem& right) {
    return left.documentName > right.documentName;
}

bool operator>(const WordItem& left, const WordItem& right) {
    return left.word > right.word;
}

template <class T>
bool binarySearch(vector<T> vec, T key) {
    int l, r;
    l = 0;
    r = vec.size() - 1;

    while (l < r) {
        int mid = l + r / 2;
        if (vec[mid] == key) {
            return true;
        }
        if (vec[mid] > key) {
            r = mid;
        }
        else {
            l = mid;
        }
    }
    return false;
}

void timing(BinarySearchTree<string, WordItem*> bst,
    HashTable<string, WordItem*> hashTable,
    vector<string>& sortedList,
    vector<string>& words,
    double& endBST,
    double& endHT) {
    int k = 100;
    clock_t begin_time = clock();
    for (int i = 0; i < k; i++) {
        for (int index = 0; index < words.size(); index++) {
            bst.search(words[index]);
        }
    }

    endBST = float(clock() - begin_time);
    cout << "\nBinary Search Tree Time: " << endBST / k << "\n";

    begin_time = clock();
    for (int i = 0; i < k; i++) {
        for (int index = 0; index < words.size(); index++) {
            hashTable.search(words[index]);
        }
    }

    endHT = float(clock() - begin_time);
    cout << "\nHash Table Time: " << endHT / k << "\n";
    begin_time = clock();
    for (int i = 0; i < k; i++) {
        for (int index = 0; index < words.size(); index++) {
            binarySearch(sortedList, words[index]);
        }
    }

    double endBS = float(clock() - begin_time);
    cout << "\nBinary Search Time: " << endBS / k << "\n";

}

int main() {
    BinarySearchTree<string, WordItem*> bst;
    HashTable<string, WordItem*> hashTable;

    //input file
    cout << "Enter number of input files: ";
    int inputFileCount;
    cin >> inputFileCount;
    vector<string> inputFileNames;
    for (int i = 1; i <= inputFileCount; i++) {
        string fileName;
        cout << "Enter " << i << ". file name: ";
        cin >> fileName;
        inputFileNames.push_back(fileName);
    }

    // read and process each document
    for (int i = 0; i < inputFileCount; i++) {
        string fileName = inputFileNames[i];

        ifstream file;
        file.open(fileName, ios::in);
        if (!file.is_open()) continue;
        WordItem* currentWordItem = nullptr;

        while (!file.eof()) {
            string line;
            getline(file, line);

            string word = "";

            // extracting words
            for (int i = 0; i < line.size(); i++) {
                char ch = line[i];
                if (isalpha(ch)) { // if alpha character
                    word += tolower(ch);
                }
                else if (word != "") {
                    currentWordItem = new WordItem(word);
                    currentWordItem->documents = new DocumentItem(fileName, 1);
                    bst.insert(word, currentWordItem);
                    hashTable.insert(word, currentWordItem);
                    word = ""; // reset
                }
            }
            // seperating word
            if (word != "") {
                currentWordItem = new WordItem(word);
                currentWordItem->documents = new DocumentItem(fileName, 1);
                bst.insert(word, currentWordItem);
                hashTable.insert(word, currentWordItem);
                word = "";
            }
        }

        file.close();
    }

    cin.ignore();

    cout << "Enter queried words in one line: ";
    string query;
    getline(cin, query);

    vector<WordItem*> results;
    istringstream iss(query);
    string queryWord;
    vector<string> words;
    while (iss >> queryWord) {
        string processedQueryWord;
        for (char ch : queryWord) {
            if (isalpha(ch)) {
                processedQueryWord += tolower(ch);
            }
        }
        words.push_back(processedQueryWord);
        WordItem* queryResult = bst.search(processedQueryWord);
        if (queryResult != nullptr) {
            results.push_back(queryResult);
        }
        else {
            cout << "No document contains the given query" << endl;
        }
    }

    results.clear();
    for (string& word : words) {
        WordItem* queryResult = hashTable.search(word);
        if (queryResult != nullptr) {
            results.push_back(queryResult);
        }
        else {
            cout << "No document contains the given query" << endl;
        }
    }

    vector<string> sortedList = words;
    quickSort(sortedList, 0, sortedList.size() - 1, "median");
    
    double endBST, endHT;

    timing(bst, hashTable, sortedList, words, endBST, endHT);

    vector<string> quickSortMedian = words;
    clock_t begin_time = clock();
    quickSort(quickSortMedian, 0, quickSortMedian.size() - 1, "median");
    double endQuickSortMedian = double(clock() - begin_time);
    cout << "Quick Sort(Median) Time: " << endQuickSortMedian << endl;


    vector<string> quickSortRandom = words;
    begin_time = clock();
    quickSort(quickSortRandom, 0, quickSortRandom.size() - 1, "random");
    double endQuickSortRandom = double(clock() - begin_time);
    cout << "Quick Sort(Random) Time: " << endQuickSortRandom << endl;


    vector<string> quickSortFirst = words;
    begin_time = clock();
    quickSort(quickSortFirst, 0, quickSortFirst.size() - 1, "first");
    double endQuickSortFirst = double(clock() - begin_time);
    cout << "Quick Sort(First) Time: " << endQuickSortFirst << endl;


    vector<string> mergeSortVec = words;
    begin_time = clock();
    mergeSort(mergeSortVec, 0, mergeSortVec.size() - 1);
    double endMergeSort = double(clock() - begin_time);
    cout << "Merge Sort Time: " << endMergeSort << endl;


    vector<string> heapSortVec = words;
    begin_time = clock();
    heapSort(heapSortVec);
    double endHeapSort = double(clock() - begin_time);
    cout << "Heap Sort Time: " << endHeapSort << endl;

    vector<string> insertionSortVec = words;
    begin_time = clock();
    insertionSort(insertionSortVec);
    double endInsertionSort = double(clock() - begin_time);
    cout << "Insertion Sort Time: " << endInsertionSort << endl;


    cout << "Speed Up BST/HST: " << endBST / endHT << endl;
    cout << "Speed Up Merge Sort/Quick Sort(Median): " << endMergeSort / endQuickSortMedian << endl;
    cout << "Speed Up Heap Sort/Quick Sort(Median): " << endHeapSort / endQuickSortMedian << endl;
    cout << "Speed Up Insertion Sort/Quick Sort(Median): " << endInsertionSort / endQuickSortMedian << endl;
    cout << "Speed Up Binary Search / Binary Search Tree Time: " << endBST / endQuickSortMedian << endl;
    cout << "Speed Up Binary Search / Hash Table Time: " << endHT / endQuickSortMedian << endl;

    return 0;
}
