#ifndef HOMEWORK3_QUICKSORT_H
#define HOMEWORK3_QUICKSORT_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

//partition the vector for quick sort
template<typename T>
int partition(vector<T>& data, int low, int high, string type) {
    srand(time(0));

    T pivot;
    if (type == "median") {
        pivot = data[(high+low) / 2];
    }
    else if (type == "random") {
        pivot = data[rand() % (high - low) + low];
    }
    else if (type == "first") {
        pivot = data[low];
    }
    int i = (low - 1);

    for (int j = low; j <= high; j++) {
        if (data[j] < pivot) {
            i++;
            swap(data[i], data[j]);
        }
    }

    swap(data[i + 1], data[high]);
    return (i + 1);
}

template<typename T>
void quickSort(vector<T>& data, int low, int high, string type) {
    int pi = partition(data, low, high, type);
    if (low < high) {
        quickSort(data, low, pi - 1, type);
        quickSort(data, pi + 1, high, type);
    }
}

template<typename T>
void printVector(const vector<T>& vec) {
    for (const auto& elem : vec)
        cout << elem << " ";
    cout << endl;
}

#endif // HOMEWORK3_QUICKSORT_H
