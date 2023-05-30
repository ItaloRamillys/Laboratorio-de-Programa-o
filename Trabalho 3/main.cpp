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

int main() {
    
    string nome = "../1_6_chars.txt";

    uint16_t *arrBytes = new uint16_t[256];
    for (int i = 0; i < 256; ++i){
        arrBytes[i] = 0;
    }

    ifstream arq(nome.data(), ios_base::in | ios_base::binary);
    
    //if (arq.fail()){ cout << "Erro" << errno; return 0;}

    if(!arq.is_open()){ cerr << "Erro de leitura";  return 0;}

    char c;
    int byte;
    while(!arq.eof())
    {
        c =  arq.get();
        byte = (int) c;
        cout << '\n' << byte;
        arrBytes[byte] = arrBytes[byte] + 1;
    }

    int count = 0;
    for (int i = 0; i < 256; ++i){
        if(arrBytes[i] > 0)
            count++;
        cout << '\n' << (char)i << ':' << arrBytes[i];
    }

    NohHuf *arv = new NohHuf[(2*count)-1];

    cout << "\nFim";

//    in.open("1_6_chars.txt", ios::in | ios::binary);

    return 0;
}
