#include "MinHeap.h"
#include "Customer.h"
#include "Event.h"
#include "Teller.h"
#include <iostream>

template<class T>
MinHeap<T>::MinHeap(int capacity){
    heap = new T[capacity];
    heapSize = 0;
}
template<class T>
int MinHeap<T>::parent(int i){
    return (i-1) / 2;
}

template<class T>
int MinHeap<T>::left(int i){
    return (2 * i + 1);
}

template<class T>
int MinHeap<T>::right(int i){
    return (2 * i + 2);
}

template<class T>
void MinHeap<T>::push(T newItem){
    heapSize++;
    heap[heapSize-1] = newItem;
    heapifyUp();
}

template<class T>
T MinHeap<T>::pop(){
    T root = heap[0];
    heap[0] = heap[heapSize-1];
    heapSize--;
    heapifyDown(0);
    return root;
}

template<class T>
T MinHeap<T>::peek(){
    return heap[0];
}

template<class T>
int MinHeap<T>::size(){
    return heapSize;
}

template<class T>
bool MinHeap<T>::empty(){
    return heapSize == 0;
}

template<class T>
void MinHeap<T>::swap(T *parent, T *child){
    T tmp = *parent;
    *parent = *child;
    *child = tmp;
}

template<class T>
void MinHeap<T>::heapifyDown(int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heapSize && heap[l] < heap[smallest])
        smallest = l;
    if (r < heapSize && heap[r] < heap[smallest])
        smallest = r;
    if (smallest != i){
        swap(&heap[i],&heap[smallest]);
        heapifyDown(smallest);
    }
}

template<class T>
void MinHeap<T>::heapifyUp(){
    int index = heapSize - 1;
    while(index != 0 && heap[parent(index)] > heap[index]){
        swap(&heap[parent(index)],&heap[index]);
        index = parent(index);
    }
}
template class MinHeap<Customer>;
template class MinHeap<Event>;
template class MinHeap<Teller>;