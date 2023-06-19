#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <bitset>
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
    //1_6_chars
    //2_100_as
    //3_vazio
    //4_texto_6_mega
    //8_linha_exponencial_ate_t
    string nomeInOut = "1_6_chars";
    string ext = ".txt";
    string nome = "../" + nomeInOut + ext;
    int countBytes = 0;

    int *arrBytes = new int[256];
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
      if((int)c == 255) break;
      byte = (int) c;
      // cout << '\n' << byte;
      arrBytes[byte] = arrBytes[byte] + 1;
      countBytes++;
    }
    

    cout << "\nContagem de cada caracter:\n";
    int count = 0;
    for (int i = 0; i < 256; ++i){
        cout<<"\nVerificando: "<< i << "-" << (char)i;
        if(arrBytes[i] > 0)
        {
          cout<<"\nCaracter encontrado: " << (char)i;
          count++;
        }
        // cout << '\n' << (char)i << ':' << arrBytes[i];
    }
    
    struct nohHeap* heap = (struct nohHeap*) malloc(count * sizeof(struct nohHeap));
    //struct nohHuf* arv = (struct nohHuf*) malloc((2 * count * sizeof(struct nohHuf)) - 1);

    struct nohHuf *arv = (struct nohHuf*) malloc((2 * count - 1) * sizeof(struct nohHuf));
    
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
    
    charToBinMap cod;
    cod = generateBin(cod, arv, totalElArv, totalElArv, "");

    string nomeArquivoSaida = nomeInOut + ".huf";

    ofstream arquivoSaida;

    arquivoSaida.open(nomeArquivoSaida, std::ios::binary);

    char x;

    int countBytesCopy = countBytes;
    cout << "\nTamanho arquivo: " << countBytes;

    int n = 0;
    while (countBytesCopy > 0) {
        countBytesCopy >>= 8;
        n++;
    }

    cout << "\nBytes necessarios arquivo: " << n;
    arquivoSaida.write(reinterpret_cast<const char *>(&count), 1);
    arquivoSaida.write(reinterpret_cast<const char *>(&countBytes), n);
    arquivoSaida.write(reinterpret_cast<const char *>(&arv), (2*count - 1)*sizeof(nohHuf));
    arquivoSaida.write(reinterpret_cast<const char *>(&count), 1);
    
    // for (int i = 0; i < (2 * count)-1; ++i)
    // {
    //   arquivoSaida.write(reinterpret_cast<const char *>(&arv[i].esq), sizeof(nohHuf::esq));
    //   arquivoSaida.write(reinterpret_cast<const char *>(&arv[i+1].dir), sizeof(nohHuf::dir));
    // }
    cout << "\n\n";
    string code;
    while(!arq.eof())
    {
      x = arq.get();
      // cout << "\nChar: " << x;
      // cout << "\nCodigo: ";
      // cout << cod[(int)x];
      //F = (uint8_t)cod[(int)x];
      code = cod[(int)x];
      //cout << "\nCode: " <<  code;

//CONTAR Ate juntar 8 bits e salva-los como 1 byte

      for (int i = 0; i < code.length(); i++) {
        if(code[i] == '0')
          arquivoSaida.put(false);
        if(code[i] == '1')
          arquivoSaida.put(true);
      }
      // for (std::size_t i = 0; i < code.size(); ++i)
      // { 
      //   if(code[i] == '0')
      //     arquivoSaida << false;
      //   else
      //     arquivoSaida << true;
      // }
      // std::bitset<sizeof(unsigned char) * 1> bits(code);

      // unsigned char binary_value = bits.to_ulong();

      // // write the binary value to file
      // arquivoSaida.write((const char*)&binary_value, sizeof(unsigned char));
      //cout << "\nBit: " <<  bitset<8>(code).to_ulong();
      //arquivoSaida << bitset<8>(code[i]);
      //arquivoSaida.write((char*)cod[(int)x].c_str(), cod[(int)x].size());
      //arquivoSaida.put((char*)cod[(int)x]);
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
    
    // nohHuf arvRead;
    cout << "\nTamanho da arvore: " << countChars << "\n\n";

    file >> byteRead;
    int countBytesFile = (int)byteRead;
    cout << "\nTamanho do arquivo origem: " << countBytesFile << "\n\n";

    nohHuf *arvRead; 
    file.read(reinterpret_cast<char*>(&arvRead), (2*countChars - 1)*sizeof(nohHuf));
    // cout << "\nTELLG: " << file.tellg();

    // file.read(reinterpret_cast<char*>(&arvRead.esq), sizeof(nohHuf::esq)); 
    // file.read(reinterpret_cast<char*>(&arvRead.dir), sizeof(nohHuf::dir));

    cout << "\nImprimindo a arvore para leitura:\n";

    for (int i = 0; i < (2 * count)-1; ++i)
    {
      cout << "\n[" << i << "]";
      cout << "Esq: " << arvRead[i].esq;
      cout << " - Dir: " << arvRead[i].dir;
    }
    
    cout << '\n';

    // char ch;
    // while (file.get(ch))          // loop getting single characters
    //   std::cout << ch;
    

    cout << '\n';
    //int startBin = (2 * count);
    int j = 0;
    //int root;
    while (!file.eof())
    {
      //cout << "\nPosicao no arquivo: " << j;
      file >> byteRead;
      //cout << byteRead;
      //cout << "\nByte lido: " << (char)byteRead;

      if (file.fail())
      {
        cout << "Error read";
          //error
          break;
      }

      //bytes.push_back(byte);
      // //cout << buffer[i];
      // cout << "\nPos: "  << j;
      //cout << "\n" << byteRead;
      //cout << "\nRoot: " << root;
      
      //   cout << "\nJ: " << j << " - Start: " << startBin;
      //   while (root >= count)
      //   {
      //     if(byteRead == 0){
      //       cout << "\nByte 0";
      //       root = arvRead[root].esq;
      //     }
      //     else if(byteRead == 1){
      //       cout << "\nByte 0";
      //       root = arvRead[root].dir;
      //     }
      //     cout<<"\nRoot atual: " << root;
      //   }

      // cout << "Char: " << (char)arvRead[root].esq;
      j++;
    }

    file.close();
    //delete[] buffer;

    return 0;
}
