#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <bitset>
#include <chrono>
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
    //cout << "\nExtraindo:";
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
        //minhaHeap();
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

void generateHuffmanTree(Heap *h, nohHuf *arv, int x)
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
    
    esq = arv[i].esq;
    dir = arv[i].dir;
    
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

void compress(string inputFileName, string outputFileName)
{
    //string inputFileNameOut = "7_linha_aleatoria_1_milhao.txt";
    inputFileName = "../" + inputFileName;
    int countBytes = 0;

    int *arrBytes = new int[256];
    for (int i = 0; i < 256; ++i){
        arrBytes[i] = 0;
    }

    ifstream inputFile(inputFileName, ios_base::in | ios_base::binary);
    
    ofstream outputFile;
    outputFile.open(outputFileName, ios::binary);

    //if (inputFile.fail()){ cout << "Erro" << errno; return 0;}

    if(!inputFile.is_open()){ cerr << "Erro de leitura";  return;}

    unsigned char c;
    int byte;

    //cout << "Caracteres do arquivo:\n";
    while(!inputFile.eof())
    {
      c = inputFile.get();
      if((int)c == 255) break;
      byte = (int) c;
      // cout << '\n' << byte;
      arrBytes[byte] = arrBytes[byte] + 1;
      countBytes++;
    }

    if(!countBytes){ cout << "\nArquivo vazio"; return; }//Se o arquivo é vazio basta criar um outro arquivo vazio

    cout << "\nContagem de cada caracter:\n";
    int count = 0;
    uint16_t firstByte;
    bool firstByteFound = false;
    for (int i = 0; i < 256; ++i){
        //cout<<"\nVerificando: "<< i << "-" << (char)i;
        if(arrBytes[i] > 0)
        {
          if(!firstByteFound)
          { 
            firstByte = i; 
            firstByteFound = true;
          }
          cout<<"\nCaracter encontrado: " << (char)i;
          count++;
        }
        // cout << '\n' << (char)i << ':' << arrBytes[i];
    }

    //Arquivo com 1 caracter que se repete
    if(count == 1)
    { 
      int n = 0;
      int aux = arrBytes[firstByte];
      while (aux > 0) {
          aux >>= 8;
          n++;
      }

      cout << "\nArquivo 1 caracter"; 
      outputFile.write(reinterpret_cast<const char *>(&count), 1);//Quantidade de caracteres
      outputFile.write(reinterpret_cast<const char *>(&firstByte), 1);//Byte encontrado
      outputFile.write(reinterpret_cast<const char *>(&n), 1);//Quantidade de bytes para representar o numero total de repeticoes
      outputFile.write(reinterpret_cast<const char *>(&arrBytes[firstByte]), n);//Quantidade de repeticoes
      outputFile.close();
      delete []arrBytes;
      return; 
    }
    
    struct nohHeap* heap = (struct nohHeap*) malloc(count * sizeof(struct nohHeap));
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
    
    //Construindo a heap
    Heap *h = new Heap(heap, ind);
    h->constroiHeap();
    //h->minhaHeap();

    //Gerando a arvore de Huffman
    generateHuffmanTree(h, arv, count);

    cout << "\nImprimindo a arvore:\n";

    for (int i = 0; i < (2 * count)-1; ++i)
    {
      cout << "\n[" << i << "]";
      cout << "Esq: " << arv[i].esq;
      cout << " - Dir: " << arv[i].dir;
    }
    cout << '\n';
    
    inputFile.close();

    charToBinMap cod;
    cod = generateBin(cod, arv, totalElArv, totalElArv, "");

    int countBytesCopy = countBytes;
    cout << "\nTamanho arquivo: " << countBytes;

    int n = 0;
    while (countBytesCopy > 0) {
        countBytesCopy >>= 8;
        n++;
    }

    cout << "\nBytes necessarios arquivo: " << n;
    outputFile.write(reinterpret_cast<const char *>(&count), 1);//Quantidade de caracteres

    cout << "\n\n";

    string code;

    char x;

    int countByte = 0;
    char byteToWrite = 0;
    char extrabits = 0; 
    int numBytes = 0; 

    streamoff extraBitsAddress = outputFile.tellp();
    outputFile.write(&extrabits, sizeof(char));
    streamoff numBytesAddress = outputFile.tellp();
    outputFile.write((char*)&numBytes, sizeof(int));

    outputFile.write(reinterpret_cast<const char *>(&arv), (2*count - 1)*sizeof(nohHuf));//Arvore de Huffman

    cout << "\nComecando leitura";
    while(!inputFile.eof())
    {
      x = inputFile.get();
      // cout << "\nChar: " << x;
      // cout << "\nCodigo: ";
      // cout << cod[(int)x];
      code = cod[(int)x];
      //cout << "\nLendo: " << code;
      for(int i = 0; i < code.length(); i++){
          if(countByte == 8){
              if(inputFile.eof()) break;
              cout << byteToWrite;
              outputFile.write(&byteToWrite, sizeof(char));
              countByte = 0;
              byteToWrite = 0;
              numBytes++;
              cout << "\nNum: " << numBytes;
          }

          byteToWrite = byteToWrite << 1; 
          if(code[i] == '1') byteToWrite = byteToWrite | (char) 1;
          countByte++;
          cout <<"AAAAAA";
      }
      //CONTAR Ate juntar 8 bits e salva-los como 1 byte
    }
    
    if(countByte != 8){ 
        extrabits = (char) 8 - countByte; //Quantos bits faltam para completar 1 byte
        numBytes++; 
        cout << "\nQuantidade de bits extras utilizados: " << (int) extrabits;
        cout << "\nQuantidade de Bytes gravados: " << numBytes;
        byteToWrite = byteToWrite << extrabits;
        outputFile.write((char*)&byteToWrite, sizeof(char));
        outputFile.seekp(extraBitsAddress);
        outputFile.write(&extrabits, sizeof(char));
        outputFile.seekp(numBytesAddress);
        outputFile.write((char*)&numBytes, sizeof(int));
    }

    outputFile.close();
    
    //Apagando todas as estruturas utilizadas
    delete h;
    delete []arrBytes;
    free(arv);
    free(heap);
}

void descompress(string inputFileName, string outputFileName)
{

    //cout <<"------DESCOMPRESSAO------\n";

    ifstream inputFile;
    inputFile.open(inputFileName, ios::binary);
    ofstream outputFile;
    outputFile.open(outputFileName, ios::binary);

    if(inputFile.peek() == std::ifstream::traits_type::eof())
    {
      cout<<"\nArquivo vazio"; 
      inputFile.close();
      outputFile.close();
      return;
    }

    uint16_t firstByte = (uint16_t)inputFile.get();
    
    if(firstByte == 1)
    {
      uint16_t byte = (uint16_t)inputFile.get();
      uint16_t sizeBytes = (uint16_t)inputFile.get();;
      long count = 0;
      inputFile.read(reinterpret_cast<char*>(&count), sizeBytes);

      cout<<"\nQuantidade:" << count;
      for (size_t i = 0; i < count; i++)
      {
        outputFile.write(reinterpret_cast<const char *>(&byte), sizeof(char));
      }

      inputFile.close();
      outputFile.close();
      return;
    }

    char byteRead;
    int countChars = (int)byteRead;
    
    // nohHuf arvRead;
    cout << "\nTamanho da arvore: " << countChars << "\n";

    inputFile >> byteRead;
    int extraBits = (int)byteRead;
    cout << "\nExtraBits: " << extraBits << "\n";

    int numBytesOutputFile;
    inputFile.read(reinterpret_cast<char*>(&numBytesOutputFile), sizeof(int));
    cout << "\nQuantidade de bytes para serem lidos em seguida: " << numBytesOutputFile << "\n";

    struct nohHuf *arvRead = (struct nohHuf*) malloc((2 * countChars - 1) * sizeof(struct nohHuf));; 
    inputFile.read(reinterpret_cast<char*>(&arvRead), (2*countChars - 1)*sizeof(nohHuf));
    
    cout << "\nImprimindo a arvore para leitura:\n";

    for (int i = 0; i < (2 * countChars)-1; ++i)
    {
      cout << "\n[" << i << "]";
      cout << "Esq: " << arvRead[i].esq;
      cout << " - Dir: " << arvRead[i].dir;
    }

    cout << '\n';
    //int startBin = (2 * count);
    int j = 0;
    //int root;
    while (!inputFile.eof())
    {
      //cout << "\nPosicao no arquivo: " << j;
      inputFile >> byteRead;
      //cout << byteRead;
      //cout << "\nByte lido: " << (char)byteRead;

      if (inputFile.fail())
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

    inputFile.close();
}

//int main() {

int main(int argc,char* argv[]) {
  
    //1_6_chars.txt
    //2_100_as.txt
    //3_vazio.txt
    //4_texto_6_mega.txt
    //5.pdf
    //6.bmp
    //7_linha_aleatoria_1_milhao.txt
    //8_linha_exponencial_ate_t.txt
    if(argc>=2) {
       string modo = argv[1];
       string inputFile = argv[2];
       string outputFile = argv[3]; 

       cout << "\nEscolha: " << modo;
       cout << "\nInputFile: " << inputFile;
       cout << "\nOutputFile: " << outputFile;

       if(modo == "-c"){
            auto start = chrono::high_resolution_clock::now();
            compress(inputFile, outputFile);
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            cout << "\nTempo comprimindo: " << duration.count() << " ms" << endl;
       } else if (modo == "-d"){
            auto start = chrono::high_resolution_clock::now();
            descompress(inputFile, outputFile);
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            cout << "\nTempo descomprimindo: " << duration.count() << " ms" << endl;
       } else if (modo == "-x"){
            
       } else {
           cout << "\nErro na leitura da entrada" << endl;
       }
            
    }

    //DESALOCAR TUDO QUE FOR POSSÍVEL

    return 0;
}
