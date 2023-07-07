#include "AVL.cpp"

int altura(Noh* n){
    if (n == nullptr)
        return -1;
    else
        return n->h;
}

void RotacaoLL(Noh *raiz);
void RotacaoRR(Noh *raiz);
void RotacaoLR(Noh *raiz);
void RotacaoRL(Noh *raiz);

int fatorBalanceamento(Noh *n){
    return labs(altura(n->esq) - altura(n->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

void RotacaoLL(Noh *raiz) {
    Noh *n;
    n = raiz->esq;
    n->dir = raiz;
    raiz->h = maior(altura(raiz->esq), altura(raiz->dir)) + 1;

    n->h = maior(altura(n->esq), raiz->h) + 1;
    raiz = n;
}

void RotacaoRR(Noh *raiz){
    Noh *n;
    raiz->dir = n->esq;
    n->esq = raiz;
    raiz->h = maior(altura(raiz->esq), altura(raiz->dir)) + 1;
    
    n->h = maior(altura(n->dir), raiz->h) + 1;
    raiz = n;
}

void RotacaoLR(Noh *raiz){
    RotacaoRR(raiz->esq);
    RotacaoLL(raiz);
}

void RotacaoRL(Noh *raiz){
    RotacaoLL(raiz->dir);
    RotacaoRR(raiz);
}