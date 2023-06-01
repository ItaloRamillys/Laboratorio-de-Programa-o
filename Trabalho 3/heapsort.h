#ifndef HEAP
#define HEAP
class Heap{
    int n;
    nohHeap *array;
    int currentSize;
    public:
    Heap(nohHeap *a, int size);
    void descer(int i);
    void heapSort();
    void constroiHeap();
    //void minhaHeap();
};
#endif