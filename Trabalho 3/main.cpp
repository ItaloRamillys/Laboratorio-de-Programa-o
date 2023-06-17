#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <map>

using namespace std;
typedef map<char, string> charToBinMap;

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

    if (l < currentSize && array[l].peso < array[m].peso)
      m = l;

    if (r < currentSize && array[r].peso < array[m].peso)
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
    cout << "\nMinha HEAP("<< this->currentSize << " - " << this->n <<"):\n";
    for (int i = 0; i < n; ++i){
      cout << "[" << i << "]" << this->array[i].ind << "=>" << this->array[i].peso;
    }
    cout << "\n";
  }

  nohHeap max(){
      return array[0];
  }

  nohHeap extractMin(){
    cout << "\nExtraindo:";
      if (this->n < 0){
          cout << "Heap underflow";
          nohHeap *n = new nohHeap();
          return *n;
      }else{
        nohHeap min = array[0];
        array[0] = array[n-1];
        this->n = this->n - 1;
        this->currentSize = this->currentSize - 1;
        descer(0);
        minhaHeap();
        return min;
      }
  }

  void inserir(nohHeap x){
    // cout << "\nInserindo(" << this->n << "): " << x.ind << " - " << x.peso;
    array[n] = x;
    this->currentSize = this->n + 1;
    this->n = this->n + 1;

    //minhaHeap();

    // cout << "\nN:" << this->n;
    // cout << "\nInicio:" << array[0].ind << '-' << array[0].peso;
    // cout << "\nFim:" << array[n-1].ind <<  '-' << array[n-1].peso;
    // cout << "\nAntes do swap:";
    //minhaHeap();
    swap(array[0], array[n-1]);
    // cout << "\nAntes de descer:";
    //minhaHeap();

    descer(0);

    // cout << "\nDepois de descer:";

    //minhaHeap();
  }
};

void comprimir(Heap *h, nohHuf *arv, int x)
{
  int n = x;
  cout << "\nComprimindo: ";
  //h->minhaHeap();
  int i = 0;
  
  nohHeap nohHeap1, nohHeap2, nohHeapInternal;
  nohHuf nHuf;
  
  int nohInterno = 0;
  while(h->currentSize > 0) 
  {
    //cout << "\nTamanho da heap: " << h->n;
    nohHeap1 = h->extractMin();
    nohHeap2 = h->extractMin();
    // cout << "\n["<<nohHeap1.ind<<"]"<<nohHeap1.peso;
    // cout << " - ["<<nohHeap2.ind<<"]"<<nohHeap2.peso;

    nHuf.esq = nohHeap1.ind;
    nHuf.dir = nohHeap2.ind;

    arv[n+i] = nHuf;
    ++i;

    nohHeapInternal.ind = n+nohInterno; nohInterno++;
    nohHeapInternal.peso = nohHeap1.peso + nohHeap2.peso;
    h->inserir(nohHeapInternal);
    //h->minhaHeap();
  }
}

charToBinMap generateBin(charToBinMap binMap, nohHuf *arv, int i, int count, string cod)
{
    int esq, dir;
    
    //cout << "\nComecando de " << ((2 * count) - 2);
    // cout << "\nIndice: " << i << ".";
    esq = arv[i].esq;
    dir = arv[i].dir;
    // cout << "\nEsq: " << esq;
    // cout << "\nDir: " << dir;
    // cout << "\nByte: " << byte;
    
    if(i <= (count/2))
    {
      binMap[arv[i].esq] = cod;
    }else
    {
      binMap = generateBin(binMap, arv, esq, count, cod+'0');
      binMap = generateBin(binMap, arv, dir, count, cod+'1');
    }

    return binMap;

}

int main() {

    string nomeInOut = "8_linha_exponencial_ate_t";
    string nome = "../" + nomeInOut + ".txt";

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
        // cout << '\n' << byte;
        arrBytes[byte] = arrBytes[byte] + 1;
    }

    cout << "\nContagem de cada caracter:\n";
    int count = 0;
    for (int i = 0; i < 256; ++i){
        if(arrBytes[i] > 0)
            count++;
        // cout << '\n' << (char)i << ':' << arrBytes[i];
    }
    
    struct nohHeap* heap = (struct nohHeap*) malloc(count * sizeof(struct nohHeap));
    //struct nohHuf* arv = (struct nohHuf*) malloc((2 * count * sizeof(struct nohHuf)) - 1);

    struct nohHuf *arv = (struct nohHuf*) malloc(2 * count * sizeof(struct nohHuf) - sizeof(struct nohHuf));
    
    int totalElArv = (2 * count)-2;

    int ind = 0;
    for (int i = 0; i < 256; ++i){
        if(arrBytes[i] > 0)
        {
            struct nohHeap noh;
            noh.ind = ind;
            noh.peso = arrBytes[i];
            heap[ind] = noh;

            struct nohHuf nohHu;
            nohHu.esq = i;
            nohHu.dir = 0;
            arv[ind] = nohHu;
            ind++;
        }
    }

    cout << "\nHeap";
    for (int i = 0; i < count; ++i){
        // cout << "\n[" << heap[i].ind << "]: " << heap[i].peso;
    }

    for (int i = 0; i < (2 * count)-1; ++i)
    {
      // cout << "\n[" << i << "]";
      // cout << "Esq: " << arv[i].esq;
      // cout << " - Dir: " << arv[i].dir;
    }
    
    Heap *h = new Heap(heap, ind);
    h->constroiHeap();
    // h->minhaHeap();

    comprimir(h, arv, count);

    cout << "\nImprimindo a arvore:\n";

    for (int i = 0; i < (2 * count)-1; ++i)
    {
      cout << "\n[" << i << "]";
      cout << "Esq: " << arv[i].esq;
      cout << " - Dir: " << arv[i].dir;
    }

    cout << '\n';

    // for (int i = 0; i < (2 * count)-1; ++i)
    // {
    //   cout << "\n[" << i << "]";
    //   cout << "Esq: " << (char)arv[i].esq;
    //   cout << " - Dir: " << (char)arv[i].dir;
    // }

    arq.clear();
    arq.seekg(0, ios::beg);
    string cadeia = "";

    charToBinMap cod;
    cod = generateBin(cod, arv, totalElArv, totalElArv, "");

    string nomeArquivoSaida = nomeInOut + ".huf";

    ofstream arquivoSaida;

    arquivoSaida.open(nomeArquivoSaida, std::ios::binary);

    char x;

    arquivoSaida.write(reinterpret_cast<const char *>(&count), sizeof(count));

    arquivoSaida.write((char*)arv, (2*count - 1)*sizeof(nohHuf));
    while(!arq.eof())
    {
      cadeia = {};
      x = arq.get();
      // cout << "\nChar: " << x;
      // cout << "\nCodigo: ";
      // cout << cod[(int)x];
      arquivoSaida.write((char*)cod[(int)x].c_str(), cod[(int)x].size());
    }
    
    arquivoSaida.close();

    // char* buffer;
    // long size;
    // ifstream file ("meuExemplo.huf", ios::in|ios::binary|ios::ate);
    // size = file.tellg();
    // file.seekg (0, ios::beg);
    // cout << "\nTamanho: " << size << "\n";
    // buffer = new char[size];
    // file.read (buffer, size);
    
    ifstream file;

    file.open(nomeArquivoSaida, ios::binary);

    //vector<unsigned char> bytes;
    //for (int i = 0; i < size; i++)
    
    unsigned char byteRead;
    file >> byteRead;
    int countChars = (int)byteRead;
    
    struct nohHuf *arvRead = (struct nohHuf*) malloc(2 * countChars * sizeof(struct nohHuf) - sizeof(struct nohHuf));

    cout << "\nTamanho da arvore: " << countChars << "\n\n";

    for (int i = 0; i < 2 * countChars - 1; i++)
    {
      file >> byteRead;
      arvRead[i].esq = (uint16_t)byteRead;
      file >> byteRead;
      arvRead[i+1].dir = (uint16_t)byteRead;
    }

    cout << "\nImprimindo a arvore para leitura:\n";

    for (int i = 0; i < (2 * count)-1; ++i)
    {
      cout << "\n[" << i << "]";
      cout << "Esq: " << arv[i].esq;
      cout << " - Dir: " << arv[i].dir;
    }

    cout << '\n';
    
    while (!file.eof())
    {
      file >> byteRead;

      if (file.fail())
      {
        cout << "Error read";
          //error
          break;
      }

      //bytes.push_back(byte);
      //cout << buffer[i];
      cout << byteRead;
    }
    

    file.close();

    cout << "\nthe complete file is in a buffer";

    //delete[] buffer;

    return 0;
}
