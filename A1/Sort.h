#ifndef SORT_H
#define SORT_H
#include "KeyValueEntry.h"
#include "String.h"

void merge(KeyValueEntry *arr, int start, int mid, int end){
    int leftSize = mid - start + 1;
    int rightSize = end - mid;
    KeyValueEntry left[leftSize];
    KeyValueEntry right[rightSize];

    for (int i = 0; i < leftSize; i++)
        left[i] = arr[start + i];
    for (int j = 0; j < rightSize; j++)
        right[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = start; //left subarray index, right subarray index, merged array index
    while(i < leftSize && j < rightSize) {
        int leftVal = left[i].getValue();
        int rightVal = right[j].getValue();
        if(leftVal > rightVal){
            arr[k] = left[i++];
        } else if (leftVal < rightVal){
            arr[k] = right[j++];
        } else {
            if(compare(left[i].getKey(),right[j].getKey()) == -1) { // if the left key is less than right key
                arr[k] = left[i++]; // place the current item in the left array before the right array item
            } else {
                arr[k] = right[j++];
            }
        }
        k++;
    }
    // append the remaining items of the subarrays to the array
    while(i < leftSize){
        arr[k++] = left[i++];
    }
    while(j < rightSize){
        arr[k++] = right[j++];
    }
}

void mergeSort(KeyValueEntry *arr, int start, int end){
    if(start >= end){
        return;
    }
    int mid = start + (end - start) / 2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, start, mid, end);
}

void bubbleSort(KeyValueEntry *arr, int size){
    for(int i = 0; i < size; i++){
        for(int j = i; j < size; j++){
            if(arr[i].getValue() < arr[j].getValue()){
                KeyValueEntry tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
            if(arr[i].getValue() == arr[j].getValue()){
                if(compare(arr[i].getKey(),arr[j].getKey()) == -1) {
                    KeyValueEntry tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
}

#endif