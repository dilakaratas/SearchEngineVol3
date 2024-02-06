#ifndef HOMEWORK3_MERGESORT_H
#define HOMEWORK3_MERGESORT_H

#include <iostream>

using namespace std;

template<typename T>
void inPlaceMerge(vector<T> array, int left, int mid, int right) {

    int const leftSize = mid - left + 1; // left part
    int const rightSize = right - mid; // right part

    int start = mid + 1;

    if (array[mid] <= array[start]) {
        return;
    }

    while (left <= mid && start <= right) {
        if (array[left] <= array[start]) {
            left++;
        }
        else {
            T value = array[start];
            int index = start;

            while (index != left) {
                array[index] = array[index - 1];
                index--;
            }

            array[left] = value;

            left++;
            mid++;
            start++;
        }
    }
}

template<typename T>
void mergeSort(vector<T> array, int const left, int const right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // calculate middle index
        mergeSort(array, left, mid); // left side sorting
        mergeSort(array, mid + 1, right); // right side sorting
        inPlaceMerge(array, left, mid, right); // merge all
    }
}

#endif // HOMEWORK3_MERGESORT_H
