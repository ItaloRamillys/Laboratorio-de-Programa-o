#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
 
void insertionsort(int a[], int inicio, int fim)
{
    for (int i = inicio + 1; i <= fim; i++)
    {
        int valor = a[i];
        int j = i;
 
        while (j > inicio && a[j - 1] > valor)
        {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = valor;
    }
}
 
// Função para particionar o array usando o esquema de partição Lomuto
int partition(int a[], int inicio, int fim)
{
    // Escolhe o elemento mais à direita como pivô do array
    int pivo = a[fim];
 
    // elementos menores que o pivô serão empurrados para a esquerda de `pIndex`
    // elementos mais do que o pivô serão empurrados para a direita de `pIndex`
    // elementos iguais podem ir de qualquer maneira
    int pIndex = inicio;
 
    // cada vez que encontramos um elemento menor ou igual ao pivô, `pIndex`
    // é incrementado, e esse elemento seria colocado antes do pivô.
    for (int i = inicio; i < fim; i++)
    {
        if (a[i] <= pivo)
        {
            swap(a[i], a[pIndex]);
            pIndex++;
        }
    }
 
    // troca `pIndex` com pivô
    swap (a[pIndex], a[fim]);
 
    // retorna `indPivo` (índice do elemento pivô)
    return pIndex;
}
 
// Partição aleatória Quicksort para reorganizar elementos no pivô
int randPartition(int a[], int inicio, int fim)
{
    // escolha um índice aleatório entre `[inicio, fim]`
    int pivoIndex = rand() % (fim - inicio + 1) + inicio;
 
    // troca o elemento final pelo elemento presente em um índice aleatório
    swap(a[pivoIndex], a[fim]);
 
    // chama o procedimento de partição
    return partition(a, inicio, fim);
}
 
// Função para executar heapsort em um determinado intervalo de elementos
void heapsort(int *inicio, int *fim)
{
    make_heap(inicio, fim);
    sort_heap(inicio, fim);
}
 
// Função para realizar introsort no array dado
void introsort(int a[], int *inicio, int *fim, int limite)
{
    // executa a ordenação por inserção se o tamanho da partição for 16 ou menor
    if ((fim - inicio) < 16) {
        insertionsort(a, inicio - a, fim - a);
    }
    // executa heapsort se a profundidade máxima for 0
    else if (limite == 0) {
        heapsort(inicio, fim + 1);
    }
    else {
        // caso contrário, execute Quicksort
        int pivo = randPartition(a, inicio - a, fim - a);
        introsort(a, inicio, a + pivo - 1, limite - 1);
        introsort(a, a + pivo + 1, fim, limite - 1);
    }
}
 
int main()
{
    int a[] = { 5, 7, -8, 9, 10, 4, -7, 0, -12, 1, 6, 2, 3, -4, -15, 12 };
    int n = sizeof(a) / sizeof(a[0]);
 
    // obtém a profundidade máxima
    int limite = log(n) * 2;
 
    // ordena o array usando introsort o algoritmo
    introsort(a, a, a + n - 1, limite);
 
    // imprime o array ordenado
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
 
    return 0;
}