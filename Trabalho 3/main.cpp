#include <fstream>
#include <iostream>
#include <limits>

using namespace std;
//using namespace chrono;

struct nohHeap{
    uint16_t ind;
    int peso;
};

struct nohHuf{
    uint16_t esq,dir;
};

class Heap{
public:
  nohHeap *array;
  int n;
  int currentSize;

  Heap(nohHeap *a, int size) {
      array = new nohHeap[size];
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

      if (l < currentSize && array[l].peso > array[m].peso)
        m = l;

      if (r < currentSize && array[r].peso > array[m].peso)
        m = r;

      if (m != i) {
        //cout << "Heap ja existe ate: " << this->currentSize << "\n";
        //cout << "TROCA [" << array[i] << "," << array[m] << "]"
        //     << "\n";
        swap(array[i], array[m]);
        descer(m);
      }
    }

    void heapSort() {
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

    void constroiHeap() {
      for (int i = n / 2 - 1; i >= 0; i--) {
        descer(i);
      }
    }

    void minhaHeap() {
      for (int i = 0; i < n; ++i){
        cout << "[" << i << "]" << (char)this->array[i].ind << " -> " << this->array[i].peso;
      }
      cout << "\n";
    }

    nohHeap max(){
        return array[0];
    }

    nohHeap extractMax(){
        if (n < 1){
            cout << "Heap underflow";
        }
        nohHeap max = array[0];
        array[0] = array[n-1];
        n = n -1;
        descer(0);

        return max;
    }
};

int main() {
    
    string nome = "../9_meu_exemplo.txt";

    uint16_t *arrBytes = new uint16_t[256];
    for (int i = 0; i < 256; ++i){
        arrBytes[i] = 0;
    }

    ifstream arq(nome.data(), ios_base::in | ios_base::binary);
    
    //if (arq.fail()){ cout << "Erro" << errno; return 0;}

    if(!arq.is_open()){ cerr << "Erro de leitura";  return 0;}

    unsigned char c;
    int byte;

    cout << "Caracteres do arquivo:\n";
    while(!arq.eof())
    {
        c =  arq.get();
        byte = (int) c;
        cout << '\n' << byte;
        arrBytes[byte] = arrBytes[byte] + 1;
    }

    cout << "\nContagem de cada caracter:\n";
    int count = 0;
    for (int i = 0; i < 256; ++i){
        if(arrBytes[i] > 0)
            count++;
        cout << '\n' << (char)i << ':' << arrBytes[i];
    }
    
    struct nohHeap* heap = (struct nohHeap*) malloc(count * sizeof(struct nohHeap));
    //struct nohHuf* arv = (struct nohHuf*) malloc((2 * count * sizeof(struct nohHuf)) - 1);

    nohHuf *arv = new nohHuf[(2 * count * sizeof(struct nohHuf)) - 1];

    int ind = 0;
    for (int i = 0; i < 256; ++i){
        if(arrBytes[i] > 0)
        {
            struct nohHeap noh;
            noh.ind = i;
            noh.peso = arrBytes[i];
            heap[ind] = noh;

            struct nohHuf nohHu;
            nohHu.esq = i;
            arv[ind] = nohHu;
            ind++;
        }
    }

    cout << "\nHeap";
    for (int i = 0; i < count; ++i){
        cout << "\n[" << heap[i].ind << (char)heap[i].ind << "]: " << heap[i].peso;
    }
    
    cout << "\nMinha heap:\n";
    Heap *h = new Heap(heap, ind);
    h->constroiHeap();
    h->minhaHeap();
    cout << h->extractMax().peso;
    h->minhaHeap();

    cout << "\nFim";

    return 0;
}
