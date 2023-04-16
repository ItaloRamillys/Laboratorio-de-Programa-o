#include <iostream>
#include <cmath>
using namespace std;
 
class Quick {

    int *arr;
    int n;

    public:
    Quick(int *a, int size) {
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            this->arr[i] = a[i];
        }
        this->n = size;
    }
    
    int pivoFixo (int inicio, int fim) 
    { 
        //Media sem estourar limite
        cout <<"\nFim: " << fim << " - Inicio: " << inicio << " - Meio: " << (floor((fim - inicio)/2) + inicio);
        return (floor((fim - inicio)/2) + inicio);
    }

    int particionar(int inicio, int fim)
    {
        cout << "\n Array antes da troca de pivo: \n";
        int i;
        for (i=inicio; i < fim + 1; i++)
            printf("%d ", arr[i]);
        printf("\n");

        int indPivo = pivoFixo(inicio, fim);
        int pivo = arr[indPivo];

        cout << "\n -- PIVO: " << pivo << "\n";

        swap(arr[indPivo], arr[inicio]);

        cout << "\n Array depois da troca de pivo: \n";
        for (i=inicio; i < fim + 1; i++)
            printf("%d ", arr[i]);
        printf("\n");

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
        cout << "\n -- Retornando: " << maiorMenor;
        return (maiorMenor);
    }

    void quickSort(int inicio, int fim)
    {
        if (inicio < fim)
        {
            int pi = particionar(inicio, fim);

            cout <<"\nChamando para o intervalo: " << inicio << "-" << pi - 1;
            quickSort(inicio, pi - 1);
            
            cout <<"\nChamando para o intervalo: " << pi + 1 << "-" << fim;
            quickSort(pi + 1, fim);
        }
    }

    void meuArray() {
        for (int i = 0; i < n; ++i)
            cout << arr[i] << " ";
        cout << "\n";
    }

};

int main(){
    int a[10] = {6, 7, 1, 4, 3, 2, 7, 8, 9, 10};
    int n = sizeof(a) / sizeof(a[0]);

    Quick *q = new Quick(a, n);

    cout << "\nArray antes: \n";
    q->meuArray();
    q->quickSort(0, n-1);
    cout << "\nOrdenado: \n";
    q->meuArray();

    return 0;
}