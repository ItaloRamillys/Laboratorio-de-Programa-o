#include <fstream>
#include <iostream>
#include <limits>
#include "heapsort.h"

using namespace std;
//using namespace chrono;

struct nohHeap{
    uint16_t ind;
    int peso;
};

struct nohHuf{
    uint16_t esq,dir;
};

Heap::Heap(nohHeap *a, int size) {
    array = new nohHeap[size];
    for (int i = 0; i < size; i++) {
        this->array[i] = a[i];
    }
    this->n = size;
    this->currentSize = size;
}

  void Heap::descer(int i) {
    int m = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < currentSize && array[l].peso > array[m].peso)
      m = l;

    if (r < currentSize && array[r].peso > array[m].peso)
      m = r;

    if (m != i) {
      //cout << "Heap ja existe ate: " << this->currentSize << "\n";
      //cout << "TROCA [" << array[i] << "," << array[m] << "]"
      //     << "\n";
      swap(array[i].ind, array[m].ind);
      swap(array[i].peso, array[m].peso);
      descer(m);
    }
  }

  void Heap::heapSort() {
    constroiHeap();
    while (this->currentSize > 0) {
      //cout << "--------------------\n";
      //minhaHeap();
      //cout << "TROCA [" << array[0] << "," << array[this->currentSize - 1]
       //    << "]"
      //     << "\n";
      swap(array[0], array[this->currentSize - 1]);
      //cout << "HEAP APOS A TROCA\n";
      //minhaHeap();
      this->currentSize--;
      //minhaHeap();
      descer(0);
      //cout << "--------------------\n";
    }
  }

  void Heap::constroiHeap() {
    for (int i = n / 2 - 1; i >= 0; i--) {
      descer(i);
    }
  }

//   void Heap::minhaHeap() {
//     for (int i = 0; i < n; ++i)
//       cout << array[i] << " ";
//     cout << "\n";
//   }

int main() {
    
    string nome = "../2_100_as.txt";

    uint16_t *arrBytes = new uint16_t[256];
    for (int i = 0; i < 256; ++i){
        arrBytes[i] = 0;
    }

    ifstream arq(nome.data(), ios_base::in | ios_base::binary);
    
    //if (arq.fail()){ cout << "Erro" << errno; return 0;}

    if(!arq.is_open()){ cerr << "Erro de leitura";  return 0;}

    unsigned char c;
    int byte;

    cout << "Letras:\n";
    while(!arq.eof())
    {
        c =  arq.get();
        byte = (int) c;
        cout << '\n' << byte;
        arrBytes[byte] = arrBytes[byte] + 1;
    }

    cout << "\nContagem:\n";
    int count = 0;
    for (int i = 0; i < 256; ++i){
        if(arrBytes[i] > 0)
            count++;
        cout << '\n' << (char)i << ':' << arrBytes[i];
    }

    struct nohHeap* heap = (struct nohHeap*) malloc(count * sizeof(struct nohHuf));
    struct nohHuf* arv = (struct nohHuf*) malloc((2 * count * sizeof(struct nohHuf)) - 1);

    int ind = 0;
    for (int i = 0; i < 256; ++i){
        if(arrBytes[i] > 0)
        {
            struct nohHeap noh;
            noh.ind = ind;
            noh.peso = arrBytes[i];
            heap[ind] = noh;
            ind++;

            struct nohHuf nohHu;
            nohHu.esq = i;
            arv[i] = nohHu;
        }
    }

    cout << "\nHeap";
    for (int i = 0; i < count; ++i){
        cout << "\n[" << heap[i].ind << "]: " << heap[i].peso;
    }
    
    cout << "\nFim";

    return 0;
}
