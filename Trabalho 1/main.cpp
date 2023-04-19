#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <random>
#include <stdlib.h>     /* srand, rand */
#include "heapsort.h"
#include "quicksort.h"

using namespace std;
using namespace chrono;

void meuArray(int **arr, int n, int m) {
    
    for (int i = 0; i < n; i++){
        cout << "Vetor [" << i << "]";
        for (int j = 0; j < m; j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

//[INICIO] Gerador de arrays
void crescente(int **arr, int i, int m)
{
    srand(time(NULL)+rand()%1000);
    int primeiro = rand()%10;
    //cout << "\nPrimeiro sorteado: " << primeiro << "\n";
    for(int j = 0; j < m; j++)
    {
        //cout << (primeiro+j) << " ";
        arr[i][j] = (primeiro+j);
    }
    //cout << "\n";
}

void decrescente(int **arr, int i, int m)
{
    srand(time(NULL)+rand()%1000);
    int primeiro = rand()%10;
    //cout << "\nPrimeiro sorteado: " << primeiro << "\n";
    for(int j = 0; j < m; j++)
    {
        //cout << (primeiro-j) << " ";
        arr[i][j] = (primeiro-j);
    }
   // cout << "\n";
}

void aleatorio(int **arr, int i, int m)
{
    //cout << "\nALEATORIO\n";
    srand(time(NULL)+rand()%1000);
    int primeiro = rand()%10;
    //cout << "\nPrimeiro sorteado: " << primeiro << "\n";
    for(int j = 0; j < m; j++)
    {
        arr[i][j] = rand()%100;
    }
    //cout << "\n";
}
//[FIM] Gerador de arrays

template <typename T>
bool gerar_pior_caso (T *v, int n) 
{ 
    return true;
}

void preencheVetores(int **meuV, char tipo, int nInstancias, int nElementos)
{
    if(tipo == 'A'){
        for(int i = 0; i < nInstancias; i++)
        {
            //cout << "\nPreenchendo de forma aleatória";
            aleatorio(meuV, i, nElementos);
        }
    }else if(tipo == 'C'){
        for(int i = 0; i < nInstancias; i++)
        {   
            //cout << "\nPreenchendo de forma crescente";
            crescente(meuV, i, nElementos);
        }
    }else if(tipo == 'D'){
        for(int i = 0; i < nInstancias; i++)
        {   
            //cout << "\nPreenchendo de forma decrescente";
            decrescente(meuV, i, nElementos);
        }
    }
}

int** copiaMatriz(int **a, int n, int m){
    int** arr = new int*[m];

    for (int i = 0; i < m; i++) {
        arr[i] = new int[n];
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            arr[i][j] = a[i][j];
        }
    }
    return arr;
}

void rodaAlgortimos(int **a, int n, int m){
    int** arr = copiaMatriz(a, n, m);
    
    float timeHS = 0;
    for(int i = 0; i < m; i++){
        Heap *h = new Heap(arr[i], n);
        
        auto inicio = steady_clock::now();
        h->heapSort();
        auto fim = steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio);
        
        printf("Tempo Heapsort: %f\n", (elapsed/1e9));
        timeHS = timeHS + elapsed.count();
        
        //cout << "\nDepois de ordenado pelo Heap\n";
        //h->minhaHeap();
        //cout << "\n";
    }
    arr = copiaMatriz(a, n, m);
    float timeQSF = 0;
    for(int i = 0; i < m; i++){
        Quick *q = new Quick(arr[i], n, 0);//0 = pivo fixo
        
        auto inicio = steady_clock::now();
        q->quickSort();
        auto fim = steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio);
        printf("Tempo Quicksort Pivo Fixo: %f\n", (elapsed/1e9));
        timeQSF = timeQSF + elapsed.count();
        //cout << "\nDepois de ordenado pelo Quick\n";
        //q->meuArray();
        //cout << "\n";
    }

    arr = copiaMatriz(a, n, m);
    float timeQSA = 0;
    for(int i = 0; i < m; i++){
        Quick *q = new Quick(arr[i], n, 1);//1 = pivo aleatorio
        
        auto inicio = steady_clock::now();
        q->quickSort();
        auto fim = steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio);
        printf("Tempo Quicksort Pivo Aleatorio: %f\n", (elapsed/1e9));
        timeQSA = timeQSA + elapsed.count();
        //cout << "\nDepois de ordenado pelo Quick\n";
        //q->meuArray();
        //cout << "\n";
    }

    printf("Tempo Heapsort: %f\n", (timeHS/1e9));
    printf("Tempo Quicksort Pivo Fixo:  %f\n", (timeQSF/1e9));
    printf("Tempo Quicksort Pivo Aleatorio:  %f\n", (timeQSA/1e9));
}
/*
int main(int argc, char *argv[]) {
    
    int nInstancias = atoi(argv[3]);
    int nElementos = atoi(argv[2]);
    int** a = new int*[nInstancias];

    for (int i = 0; i < nInstancias; i++) {
        a[i] = new int[nElementos];
    }

    preencheVetores(a, *argv[1], nInstancias, nElementos);

    rodaAlgortimos(a, nElementos, nInstancias);

    /*
    int* ptr1;
    int* ptr2;
    int* ptr3;
    int n;

    cout << "Digite um numero: ";
    cin >> n;

    ptr1 = crescente(n);
    ptr2 = decrescente(n);
    ptr3 = aleatorio(n);

    cout <<"\nCrescente";
    for(int i=0 ; i<n; i++)
    {
		cout<<"\n"<<ptr1[i];
    }

    cout <<"\nDecrescente";
    for(int i=0 ; i<n; i++)
    {
		cout<<"\n"<<ptr2[i];
    }

    cout <<"\nAleatorio";
    for(int i=0 ; i<n; i++)
    {
		cout<<"\n"<<ptr3[i];
    }

	return 0;
}
*/