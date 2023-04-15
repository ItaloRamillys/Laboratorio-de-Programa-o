#include <iostream>
using namespace std;

class Heap {
  int n;
  int *array;
  int currentSize;

  public:
  Heap(int *a, int size) {
    array = new int[size];
    for (int i = 0; i < size; i++) {
      this->array[i] = a[i];
    }
    this->n = size;
    this->currentSize = size;
  }

  void descer(int i) {
    int m = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < currentSize && array[l] > array[m])
      m = l;

    if (r < currentSize && array[r] > array[m])
      m = r;

    if (m != i) {
      cout << "Olhando ate a posicao: " << this->currentSize << "\n";
      cout << "TROCA [" << array[i] << "," << array[m] << "]"
           << "\n";
      swap(array[i], array[m]);
      descer(m);
    }
  }

  void heapSort() {

    while (this->currentSize > 0) {
      cout << "--------------------\n";
      minhaHeap();
      cout << "TROCA [" << array[0] << "," << array[this->currentSize - 1]
           << "]"
           << "\n";
      swap(array[0], array[this->currentSize - 1]);
      cout << "HEAP APOS A TROCA\n";
      minhaHeap();
      this->currentSize--;
      minhaHeap();
      descer(0);
      cout << "--------------------\n";
    }
  }

  void minhaHeap() {
    for (int i = 0; i < n; ++i)
      cout << array[i] << " ";
    cout << "\n";
  }
};

int main() {
  int a[10] = {6, 7, 1, 4, 3, 2, 7, 8, 9, 10};
  int n = sizeof(a) / sizeof(a[0]);

  Heap *h = new Heap(a, n);

  h->minhaHeap();
  for (int i = n / 2 - 1; i >= 0; i--) {
    h->descer(i);
  }

  cout << "Array -> Heap\n";
  h->minhaHeap();
  h->heapSort();
  cout << "Heap -> HeapSort\n";
  h->minhaHeap();

  return 0;
}
