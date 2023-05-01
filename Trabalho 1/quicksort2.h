#ifndef QUICK2
#define QUICK2
class Quick2{
    int *arr;
    int n;
    int tipoPivo; //0 = fixo || 1 == aleatorio
    public:
    Quick2(int *a, int size, int tipoPivo);
    int* array ();
    int pivoFixo (int inicio, int fim);
    int pivoAleatorio (int inicio, int fim);
    int particionar(int inicio, int fim, int &i);
    void quickSort();
    void _quickSort(int inicio, int fim, int *i);
    void meuArray();
};
#endif