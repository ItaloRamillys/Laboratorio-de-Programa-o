#ifndef HEAP
#define HEAP
class Heap{
    int n;
    int *array;
    int currentSize;
    public:
    Heap(int *a, int size);
    void descer(int i);
    void heapSort();
    void constroiHeap();
    void minhaHeap();
};
#endif