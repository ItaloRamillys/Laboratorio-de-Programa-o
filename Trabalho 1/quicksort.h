#ifndef QUICK
#define QUICK
class Quick{
    int *arr;
    int n;
    int tipoPivo; //0 = fixo || 1 == aleatorio
    public:
    Quick(int *a, int size, int tipoPivo);
    int pivoFixo (int inicio, int fim);
    int pivoAleatorio (int inicio, int fim);
    int particionar(int inicio, int fim);
    void quickSort();
    void _quickSort(int inicio, int fim);
    void meuArray();
};
#endif