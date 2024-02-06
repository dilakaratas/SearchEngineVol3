#ifndef HOMEWORK3_INSERTIONSORT_H
#define HOMEWORK3_INSERTIONSORT_H

#include <iostream>

using namespace std;

template<typename T>
void insertionSort(vector<T>& arr) {
    int n = arr.size();
    int currentPosition, previousPosition;
    T key;

    for (currentPosition = 1; currentPosition < n; currentPosition++) {
        key = arr[currentPosition];
        previousPosition = currentPosition - 1;

        while (previousPosition >= 0 && arr[previousPosition] > key) {
            arr[previousPosition + 1] = arr[previousPosition];
            previousPosition = previousPosition - 1;
        }

        arr[previousPosition + 1] = key;
    }
}

#endif //HOMEWORK3_INSERTIONSORT_H
