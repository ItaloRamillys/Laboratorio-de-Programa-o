#include <exception>
#include <iostream>
using namespace std;

#include "solucao.hpp"
int main ()
{
    try
    {
        DicioAVL<int,char> D;
        
        DicioAVL<int,char>::Iterador its[10], it;
        int i;
        for (i = 48; i < 58; ++i)
        {
            it = D.inserir(i, (char) i); if (it == D.end()) return 2;
            its[i-48] = it;
        }
        for (it = D.begin(); it != D.end(); ++it)
        {
            cout << "O codigo de " << it.valor()
            << " e " << it.chave() << '\n';
        }
        for (i = 48; i < 58; ++i)
        {
            it = D.buscar(i); if (it != its[i-48]) return 2;
            D.remover(it);
        }
        cout << "Executou o teste basico conforme esperado.\n";
    }
    catch (const exception &e)
    {
        cerr << "Excecao: " << e.what() << '\n'; return 1;
    }
} // main
