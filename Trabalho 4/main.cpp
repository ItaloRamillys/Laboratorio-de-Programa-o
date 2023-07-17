#include <exception>
#include <iostream>
using namespace std;


#include "solucao.hpp"
int main()
{
    try
    {
        DicioAVL<int, char> D;
        DicioAVL<int, char>::Iterador its[10], it;
        int i;
        for (i = 48; i < 58; ++i)
        {
            cout<<"\n---------------------------------------\n";
            it = D.inserir(i, (char)i);
            cout << "\n\n[MAIN] - Valor inserido: " << it.valor() << "\n\n";
            if (it == D.end())
            {
                cout << "\n[MAIN] - Achei sentinela";
                return 2;
            }
           
            its[i - 48] = it;

        }

        //cout<< "\nBegin: " << D.begin().valor();
        //cout <<"\nSentinela: " << ;
        //cout << "\nEnd: " << D.end().valor();

        for (it = D.begin(); it != D.end(); ++it)
        {
            cout << "\n[MAIN] - O codigo de '" << it.valor()
                 << "' e " << it.chave() << '\n';
        }
        
        //cout<< "\nIterador: " << it.valor();
        cout << "\n\n[MAIN] - Buscando:";
        for (i = 48; i < 58; ++i)
        {
            cout <<"\n[MAIN] - Chave: " << i;
            it = D.buscar(i);
            cout <<"\n[MAIN] - Valor: " << it.valor();
            if (it != its[i - 48])
                return 2;
            D.remover(it);
        }

        for (it = D.begin(); it != D.end(); ++it)
        {
            cout << "\n[MAIN] - O codigo de '" << it.valor()
                 << "' e " << it.chave() << '\n';
        }
        cout << "\n[MAIN] - Executou o teste basico conforme esperado.\n";
    }
    catch (const exception &e)
    {
        cerr << "Excecao: " << e.what() << '\n';
        return 1;
    }
} // main