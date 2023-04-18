#ifndef QUICK
#define QUICK
class Quick{
    int *arr;
    int n;
    public:
    Quick(int *a, int size);
    int pivoFixo (int inicio, int fim);
    int particionar(int inicio, int fim);
    void quickSort();
    void _quickSort(int inicio, int fim);
    void meuArray();
};
#endif