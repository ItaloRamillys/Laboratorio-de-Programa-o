#include <iostream>
#include <cmath>
#include <chrono>
#include <random>
#include <stdlib.h>
#include "quicksort2.h"
#include "quicksort.h"

using namespace std;
using namespace chrono;
 
    Quick2::Quick2(int *a, int n, int tipoPivo) {
        arr = new int[n];
        for (int i = 0; i < n; i++) {
            this->arr[i] = a[i];
        }
        this->n = n;
        this->tipoPivo = tipoPivo;
    }
    
    int* Quick2::array ()
    {
        return this->arr;
    } 

    int Quick2::pivoAleatorio (int inicio, int fim) 
    { 
        //Media sem estourar limite
        //cout <<"\nFim: " << fim << " - Inicio: " << inicio << " - Meio: " << (floor((fim - inicio)/2) + inicio);
        return (rand() % (fim - inicio + 1) + inicio);
    }
    
    int Quick2::pivoFixo (int inicio, int fim) 
    { 
        //Media sem estourar limite
        //cout <<"\nFim: " << fim << " - Inicio: " << inicio << " - Meio: " << (floor((fim - inicio)/2) + inicio);
        return (floor((fim - inicio)/2) + inicio);
    }

    int Quick2::particionar(int inicio, int fim, int &i)
    {
        int indPivo;
        
        indPivo = pivoFixo(inicio, fim);
        arr[indPivo] = i;

        i = i + 1;
        
        return (indPivo);
    }

    void Quick2::quickSort()
    {
        int i = 1;
        _quickSort(0, n-1, &i);
    }

    void Quick2::_quickSort(int inicio, int fim, int *i)
    {
        if (inicio <= fim)
        {
            int pi = particionar(inicio, fim, *i);

            //cout <<"\nChamando para o intervalo: " << inicio << "-" << pi - 1;
            _quickSort(inicio, pi - 1, i);
            
            //cout <<"\nChamando para o intervalo: " << pi + 1 << "-" << fim;
            _quickSort(pi + 1, fim, i);
        }
    }

    void Quick2::meuArray() {
        for (int i = 0; i < n; ++i)
            cout << arr[i] << " ";
        cout << "\n";
    }


int* aleatorio2(int n)
{
    int *array = new int[n];
    srand(time(NULL));
    for(int i = 0; i < n; i++)
    {   
        array[i] = i;
    }
    return array;
}
  
//Percebemos que o COUT muda completamente o tempo de execução
/*
int main(){
    int n = 30000000;
    int *a = aleatorio2(n);
    int *b = aleatorio2(n);

    Quick2 *q = new Quick2(a, n, 0);

    //cout << "\nArray antes: \n";
    //q->meuArray();
    
    q->quickSort();//Gera pior caso
    
    
    cout << "\nArray com pior caso: \n";
    //q->meuArray();

    Quick *q3 = new Quick(b, n, 0);
    Quick *q2 = new Quick(q->array(), n, 0);
    auto inicio = steady_clock::now();
    q2->quickSort();
    auto fim = steady_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio);
    
    cout << "\nArray ordenado: \n";
    //q2->meuArray();
    
    
    cout << "\nArray com caso aleatorio: \n";
    //q3->meuArray();
    auto inicio2 = steady_clock::now();
    q3->quickSort();
    auto fim2 = steady_clock::now();

    cout << "\nArray ordenado: \n";
    //q3->meuArray();

    auto elapsed2 = std::chrono::duration_cast<std::chrono::nanoseconds>(fim2 - inicio2);
    printf("\nTempo gasto caso aleatorio: %.15f segundos.\n", elapsed2.count() * 1e-9);
    printf("\nTempo gasto pior caso: %.15f segundos.\n", elapsed.count() * 1e-9);


    return 0;
}
*/