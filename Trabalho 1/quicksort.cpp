#include <iostream>
#include <cmath>
#include <chrono>
#include <random>
#include <stdlib.h>
#include "quicksort.h"

using namespace std;
using namespace chrono;
 
    Quick::Quick(int *a, int n, int tipoPivo) {
        arr = new int[n];
        for (int i = 0; i < n; i++) {
            this->arr[i] = a[i];
        }
        this->n = n;
        this->tipoPivo = tipoPivo;
    }
    
    int Quick::pivoFixo (int inicio, int fim) 
    { 
        //Media sem estourar limite
        //cout <<"\nFim: " << fim << " - Inicio: " << inicio << " - Meio: " << (floor((fim - inicio)/2) + inicio);
        return (rand() % (fim - inicio + 1) + inicio);
    }
    
    int Quick::pivoAleatorio (int inicio, int fim) 
    { 
        //Media sem estourar limite
        //cout <<"\nFim: " << fim << " - Inicio: " << inicio << " - Meio: " << (floor((fim - inicio)/2) + inicio);
        return (floor((fim - inicio)/2) + inicio);
    }

    int Quick::particionar(int inicio, int fim)
    {
        //cout << "\n Array antes da troca de pivo: \n";
        
        //for (i=inicio; i < fim + 1; i++)
        //    printf("%d ", arr[i]);
        //printf("\n");

        int indPivo;
        
        if(this->tipoPivo == 0)
            indPivo = pivoFixo(inicio, fim);
        else
            indPivo = pivoAleatorio(inicio, fim);
        int pivo = arr[indPivo];

        //cout << "\n -- PIVO: " << pivo << "\n";

        swap(arr[indPivo], arr[inicio]);

        //cout << "\n Array depois da troca de pivo: \n";
        //for (i=inicio; i < fim + 1; i++)
            //printf("%d ", arr[i]);
        //printf("\n");

        //Controle do intervalo
        int indFim = fim;
        int indInicio = inicio;
        int maiorMenor;

        while(indFim >= indInicio)
        {
            if (arr[indInicio] > pivo)
            {
                swap(arr[indInicio], arr[indFim]);
                indFim--;
            }else
            {
                maiorMenor = indInicio;
                indInicio++;
            }
            
        }

        swap(arr[inicio], arr[maiorMenor]);
        //cout << "\n -- Retornando: " << maiorMenor;
        return (maiorMenor);
    }

    void Quick::quickSort()
    {
        _quickSort(0, n-1);
    }

    void Quick::_quickSort(int inicio, int fim)
    {
        if (inicio < fim)
        {
            int pi = particionar(inicio, fim);

            //cout <<"\nChamando para o intervalo: " << inicio << "-" << pi - 1;
            _quickSort(inicio, pi - 1);
            
            //cout <<"\nChamando para o intervalo: " << pi + 1 << "-" << fim;
            _quickSort(pi + 1, fim);
        }
    }

    void Quick::meuArray() {
        for (int i = 0; i < n; ++i)
            cout << arr[i] << " ";
        cout << "\n";
    }


/*
int* aleatorio(int n)
{
    int *array = new int[n];
    srand(time(NULL));
    for(int i = 0; i < n; i++)
    {   
        array[i] = rand()%100;
    }
    return array;
}
//Percebemos que o COUT muda completamente o tempo de execução
int main(){
    int n = 10;
    int *a = aleatorio(n);

    Quick *q = new Quick(a, n);

    cout << "\nArray antes: \n";
    q->meuArray();
    
    auto inicio = steady_clock::now();
    q->quickSort();
    auto fim = steady_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio);
    
    printf("\nTempo gasto: %.8f segundos.\n", elapsed.count() * 1e-9);

    cout << "\nOrdenado: \n";
    q->meuArray();

    return 0;
}*/