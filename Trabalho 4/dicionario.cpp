#include <exception>
#include <iostream>

using std::exception;
using std::cout;

template <typename TC, typename TV>
class Dicio
{
private:
    struct Noh
    {
        TC chave;
        TV valor;
        Noh *pai, *esq, *dir;
    };

    Noh *raiz;
    Noh *primeiro;

public:
    class Iterador
    {
    private:
        Noh *n;

    public:
        Iterador(Noh *noh) : n(noh) {}

        void operator++() {
            TC chave = n->chave;
            while (true){
                if (n->dir != nullptr && n->dir->chave > chave){
                    n = n->dir;
                    while (n->esq != nullptr)
                        n = n->esq;
                    break;
                    
                }else{
                    if (n->pai != nullptr){
                        if(n->pai->esq == n){
                            n = n->pai;
                            break;
                        }else{
                            n = n->pai;
                        }
                    }else{
                        n = nullptr;
                        break;
                    }
                }
            }
        }

        TV operator*() { return n->valor; }

        bool operator!=(const Iterador &i) { return n != i.n; }
    };

    // Costrutor
    Dicio() : raiz(nullptr), primeiro(nullptr) {}
    // Destrutor
    ~Dicio(){
        // for (auto i = inicio(); i != fim(); ++i){
        //     cout << "Elemento Destruido: " << *i << '\n';
        // }
        cout << "Aqui vamos Destruir a arvore" << '\n';
    };

    Iterador inserir(TC c, TV v)
    {
        Noh *n = new Noh;
        n->chave = c;
        n->valor = v;

        if(raiz == nullptr){
			raiz = n;
            primeiro = raiz;
        }
		else{
            Noh *nohAtual = raiz;
			while(true){
                if(n->chave < nohAtual->chave){
                    if(nohAtual->esq == nullptr){
                        nohAtual->esq = n;
                        if(n->chave < primeiro->chave)
                            primeiro = nohAtual->esq;
                        n->pai = nohAtual;
                        break;
                    }
                    else
                        nohAtual = nohAtual->esq;
                }
                else{
                    if(nohAtual->dir == nullptr){
                        nohAtual->dir = n;
                        n->pai = nohAtual;
                        break;
                    }
                    else
                        nohAtual = nohAtual->dir;
                }
            }
        }
        Iterador i(n);
        return i;
    }

    Iterador procurar (TC c)
    {
        while(raiz != nullptr){
            if (raiz->chave == c){
                Iterador i(raiz);
                return i;
            }
            if (c < raiz->chave)
                raiz = raiz->esq;
            else
                raiz = raiz->dir;
        }
        Iterador i(nullptr);
        return i;
    }

    void remover (Iterador i)
    {
        Noh *aux = i;

        cout << *i << '\n';
    }

    Iterador inicio()
    {
        Iterador i(primeiro);
        return i;
    }

    Iterador fim()
    {
        Iterador i(nullptr);
        return i;
    }
};

int main()
{
    try
    {
        Dicio<double, char> D;

        Dicio<double, char>::Iterador elemAdicionado = nullptr;
        elemAdicionado = D.inserir(8, 'k');
        elemAdicionado = D.inserir(9, '9');
        elemAdicionado = D.inserir(4, '4');
        elemAdicionado = D.inserir(6, '6');
        elemAdicionado = D.inserir(5, '5');
        elemAdicionado = D.inserir(7, '7');
        elemAdicionado = D.inserir(2, '2');
        elemAdicionado = D.inserir(3, '3');
        elemAdicionado = D.inserir(1, '1');

        // auto elemEncontrado = D.procurar(5);

        // D.remover(elemAdicionado);


        // Dicio<char, double>::Iterador fim = D.fim(); // ou "auto fim ..."

        auto inicio = D.inicio();
        auto fim = D.fim();

        for (auto i = inicio; i != fim; ++i)
            cout << *i << '\n';
    }
    catch (const exception &e)
    {
        cout << "EXCEÇÃO: " << e.what() << '\n';

        return 1;
    }
}

// g++ -Wall -Wextra -std=c++17 -pedantic -o dic dicionario.cpp