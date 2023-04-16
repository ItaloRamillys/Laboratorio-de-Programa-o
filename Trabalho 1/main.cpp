#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//[INICIO] Gerador de arrays
int* crescente(int n)
{
    int *array = new int[n];
    for(int i = 0; i < n; i++)
    {
        array[i] = i;
    }
    return array;
}

int* decrescente(int n)
{
    int *array = new int[n];
    for(int i = n-1; i >= 0; i--)
    {
        array[i] = n-i;
    }
    return array;
}

int* aleatorio(int n)
{
    int *array = new int[n];
    for(int i = 0; i < n; i++)
    {
        array[i] = rand()%100;
    }
    return array;
}
//[FIM] Gerador de arrays

template <typename T>
bool gerar_pior_caso (T *v, int n) 
{ 
    return true;
}

int main() {
  
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
		cout<<"\n"<<ptr1[i]; //*(ptr+i)
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
