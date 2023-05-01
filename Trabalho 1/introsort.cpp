#include <bits/stdc++.h>
using namespace std;

class Intro{

    int *arr;
    int n;
    int currentSize;

    public:
    Intro(int *a, int size) {
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            this->arr[i] = a[i];
        }
        this->n = size;
        this->currentSize = size;
    }

    void descer(int i) {
        int m = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < currentSize && arr[l] > arr[m])
        m = l;

        if (r < currentSize && arr[r] > arr[m])
        m = r;

        if (m != i) {
        cout << "Olhando ate a posicao: " << this->currentSize << "\n";
        cout << "TROCA [" << arr[i] << "," << arr[m] << "]"
            << "\n";
        swap(arr[i], arr[m]);
        descer(m);
        }
    }

    //HEAP
    void heapSort(int inicio, int fim) {
        constroiHeap(inicio, fim);
        while (this->currentSize > 0) {
            cout << "--------------------\n";
            printarr();
            swap(arr[inicio], arr[this->currentSize - 1]);
            printarr();
            cout << "HEAP APOS A TROCA\n";
            this->currentSize--;
            descer(inicio);
            cout << "--------------------\n";
        }
    }

    void constroiHeap(int inicio, int fim) {
        this->currentSize = fim;
        for (int i = (fim - inicio) / 2 - 1; i >= inicio; i--) {
            //cout << "\nDescendo: " << i << "\n";
            descer(i);
        }
    }
    
    // void InsertionSort(int arr[], int *inicio, int *fim) {
    //     int left = inicio - arr;
    //     int right = fim - arr;

    //     for (int i = left + 1; i <= right; i++) {
    //         int key = arr[i];
    //         int j = i - 1;

    //         /* Move elements of arr[0..i-1], that are
    //         greater than key, to one position ahead
    //         of their current position */
    //         while (j >= left && arr[j] > key) {
    //         arr[j + 1] = arr[j];
    //         j = j - 1;
    //         }
    //         arr[j + 1] = key;
    //     }

    //     return;
    // }

    //QUICK
    int pivoFixo (int inicio, int fim) 
    { 
        //Media sem estourar limite
        //cout <<"\nFim: " << fim << " - Inicio: " << inicio << " - Meio: " << (floor((fim - inicio)/2) + inicio);
        return (floor((fim - inicio)/2) + inicio);
    }

    int particionar(int inicio, int fim)
    {
        cout << "\n arr antes da troca de pivo: \n";
        int i;
        for (i=inicio; i <= fim; i++)
            printf("%d ", arr[i]);
        printf("\n");

        int indPivo = pivoFixo(inicio, fim);
        int pivo = arr[indPivo];

        cout << "\n -- INDICE PIVO: " << indPivo << "\n";
        cout << "\n -- PIVO: " << pivo << "\n";

        swap(arr[indPivo], arr[inicio]);

        cout << "\n arr depois da troca de pivo: \n";
        for (i=inicio; i <= fim; i++)
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
                cout << "\nTrocando indices: " << indInicio << " - " << indFim << "\n";
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
        
        cout << "\n -- Array depois de posicionar o pivo: \n";
        
        for (i=inicio; i <= fim; i++)
            printf("%d ", arr[i]);
        printf("\n");
        return (maiorMenor);
    }
    
    void introsortUtil(int inicio, int fim, int limite) {

        /*
        if (limite < 16) {
            InsertionSort(arr, inicio, fim);
            return;
        }
        */
        
        //cout << "\nProfundidade: " << limite << "\n\n";
        
        if (limite < 8) {
            cout << "\nFAZENDO O HEAP SORT\n";
            heapSort(inicio, fim);
            return;
        }

        cout << "\nFAZENDO O Quick SORT\n";
        int particao = particionar(inicio, fim-1);

        cout << "\nFim: " << fim << " Inicio: " << inicio << "\n";
        

        cout << "IntrosortUtil > " << inicio << " - "  << particao - 1;
        cout << "IntrosortUtil > " << particao+1 << " - " << fim;
        
        introsortUtil(inicio, particao - 1, limite - 1);
        introsortUtil(particao + 1, fim, limite - 1);
        
        return;
    }

    void introsort(int inicio, int fim) {
        // log na base 2
        int i = 0;
        int dif = fim - inicio;

        while (dif >= 1) {
            dif >>= 1;
            i++;
        }

        int limite = 2 * i;

        introsortUtil(inicio, fim, limite);

        return;
    }

    void printarr() {
        for (int i = 0; i < this->n; i++)
            printf("%d ", this->arr[i]);
        printf("\n");
    }
};

int* aleatorio(int n)
{
    int *array = new int[n];
    for(int i = 0; i < n; i++)
    {
        array[i] = rand()%100;
    }
    return array;
}
/*
int main() {
    int n = 80;
    int *arr = aleatorio(n);
    //int n = sizeof(arr) / sizeof(arr[0]);

    Intro *intro = new Intro(arr,n);
    cout<<"\nArray antes:\n";
    intro->printarr();

    intro->introsort(0,n);
    cout << "\nArray ordenado: \n";
    intro->printarr();

    return 0;
}*/