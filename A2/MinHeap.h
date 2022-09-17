#ifndef MIN_HEAP_H
#define MIN_HEAP_H

template<class T>
class MinHeap {
    private:
        int heapSize;
        T *heap;
        int parent(int i);
        int left(int i);
        int right(int i);
    public:
        MinHeap(int capacity);
        void push(T newItem);
        T pop();
        T peek();
        int size();
        bool empty();
        void swap(T *parent, T *child);
        void heapifyDown(int i);
        void heapifyUp();
};

#endif
