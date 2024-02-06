#ifndef HOMEWORK3_HEAPSORT_H
#define HOMEWORK3_HEAPSORT_H

#include <iostream>
using namespace std;

template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}


// left right and find largest and swap
template<typename T>
void heapify(vector<T>& arr, int arraySize, int rootIndex) {
    int largest = rootIndex;
    int leftChild = 2 * rootIndex + 1;
    int rightChild = 2 * rootIndex + 2;

    if (leftChild < arraySize && arr[leftChild] > arr[largest])
        largest = leftChild;

    if (rightChild < arraySize && arr[rightChild] > arr[largest])
        largest = rightChild;

    if (largest != rootIndex) {
        swap(arr[rootIndex], arr[largest]);
        heapify(arr, arraySize, largest);
    }
}


//extracts max element place to at the end of the array
template<typename T>
void heapSort(vector<T>& arr) {
    int arraySize = arr.size();
    for (int i = arraySize / 2 - 1; i >= 0; i--)
        heapify(arr, arraySize, i);

    for (int i = arraySize - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

#endif // HOMEWORK3_HEAPSORT_H
