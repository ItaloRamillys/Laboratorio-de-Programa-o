#include <exception>
#include <iostream>

using std::exception;
using std::cout;

typedef double TC; typedef float TV;
struct Noh
{
	TC chave;
	TV valor;
	Noh* esq, * dir, * pai;
	int h;
};

struct DicAVL {
	Noh* raiz;
};

void inicializar(DicAVL& D);
Noh* inserir(DicAVL& D, TC c, TV v);
Noh* procurar(DicAVL& D, TC c);
void remover(DicAVL& D, Noh* n);
void terminar(DicAVL& D);

// Funções Auxiliares

int max(int a, int b)
{
	return (a > b) ? a : b;
}
int getAltura(Noh* n)
{
	if (n == nullptr)
		return 0;
	else
		return n->h;
}
int getFB(Noh* n) // Fator de difamento
{
	if (n == nullptr)
		return 0;
	else
		return (getAltura(n->esq) - getAltura(n->dir));
}

void printNoh(Noh* x)
{
	cout<<"\nNoh: "<<x->chave<<" | Valor: "<<x->valor<<"\n";
}

Noh* rotacaoDireita(Noh* y)
{
	cout << "\nRotacao em[D]: " << y->chave;
	Noh* ey = y->esq;
	Noh* dy = ey->dir;

	ey->dir = y;
	y->esq = dy;

	y->h = max(getAltura(y->esq), getAltura(y->dir)) + 1;
	ey->h = max(getAltura(ey->esq), getAltura(ey->dir)) + 1;

	printNoh(ey);
	return ey;
}

Noh* rotacaoEsquerda(Noh* y)
{
	cout << "\nRotacao em[E]: " << y->chave;
	Noh* dy = y->dir;
	cout << "1";
	Noh* ey = dy->esq;
	cout << "2";

	dy->esq = y;
	cout << "3";
	y->dir = ey;
	cout << "4";

	y->h = max(getAltura(y->esq), getAltura(y->dir)) + 1;
	dy->h = max(getAltura(dy->esq), getAltura(dy->dir)) + 1;
	
	printNoh(dy);
	return dy;
}

// Fim


void inicializar(DicAVL& D) {
	D.raiz = nullptr;
}

Noh* inserir(Noh* n, Noh* lp, TC c, TV v) {
	cout << "\nInserir\nChave:"<<c<<"\nValor:"<<v<<"\n";
	if (n == nullptr) {
		cout << "\nInserindo na folha";
		Noh *n = new Noh;

		
		if(n != lp)
		{
			cout << "\nRaiz != pai";
			n->pai = lp;
		}
		else
		{
			cout << "\nRaiz == pai";
			n->pai = nullptr;
		}
		n->esq = n->dir = nullptr;
		n->chave = c;
		n->valor = v;
		n->h = 1;
		return n;
	}

	cout << '\n';
	if (c < n->chave) 
	{
		// cout << c << " < " << n->chave << " - e";
		n->esq = inserir(n->esq, n, c, v);
	}
	else if (c > n->chave) 
	{
		// cout << c << " < " << n->chave << " - d";
		n->dir = inserir(n->dir, n, c, v);
	}
	else{
		return nullptr;
		cout << "\nChave duplicada \n";
	}
	// cout << "\nRaiz observada: " << n->chave;
	n->h = 1 + max(getAltura(n->esq), getAltura(n->dir));

	int dif = getFB(n);

	cout << "\nDif: " << dif << ' ';

	if (dif < -1 && c > n->dir->chave)
	{
		// cout <<"\nRotacao Esq NEGATIVO";
		return rotacaoEsquerda(n);
	}
	if (dif < -1 && c < n->dir->chave) {
		// cout <<"\nRotacao Dir NEGATIVO";
		n->dir = rotacaoDireita(n->dir);
		return rotacaoEsquerda(n);
	}
	
	if (dif > 1 && c < n->esq->chave)
	{
		// cout <<"\nRotacao Dir POSITIVO";
		return rotacaoDireita(n);
	}
	if (dif > 1 && c > n->esq->chave) {
		// cout <<"\nRotacao Esq POSITIVO";
		n->esq = rotacaoEsquerda(n->esq);
		return rotacaoDireita(n);
	}

	return n;
}

Noh* inserir(DicAVL& D, TC c, TV v) {
	if (D.raiz == nullptr)
		return D.raiz = inserir(D.raiz, D.raiz, c, v);
	else
		return D.raiz = inserir(D.raiz, D.raiz, c, v);
}

void printArv(Noh *raiz)
{
    if(raiz != nullptr)
    {
        cout <<'\n'<< raiz->chave;
		if( raiz->pai != nullptr )
			cout << " | Pai: " << raiz->pai->chave;
		else
			cout << " | Pai: NULO";
		if( raiz->esq != nullptr )
			cout << " | Esq: " << raiz->esq->chave;
		else
			cout << " | Esq: NULO";
		if( raiz->dir != nullptr )
			cout << " | Dir: " << raiz->dir->chave;
		else
			cout << " | Dir: NULO";
        printArv(raiz->esq);
        printArv(raiz->dir);
    }
}

Noh* menorChave(Noh* no)
{
    Noh* atual = no;

    while (atual->esq != NULL)
        atual = atual->esq;
 
    return atual;
}

Noh* deletar(Noh* raiz, TC chave)
{
    
    if (raiz == NULL)
        return raiz;
 
    if ( chave < raiz->chave )
        raiz->esq = deletar(raiz->esq, chave);
 
    else if( chave > raiz->chave )
        raiz->dir = deletar(raiz->dir, chave);
 
    else
    {
        if( (raiz->esq == NULL) ||
            (raiz->dir == NULL) )
        {
            Noh *temp = raiz->esq ?
                         raiz->esq :
                         raiz->dir;
 
            if (temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else
            *raiz = *temp;
            free(temp);
        }
        else
        {
            Noh* temp = menorChave(raiz->dir);
 
            raiz->chave = temp->chave;
 
            raiz->dir = deletar(raiz->dir,
                                     temp->chave);
        }
    }
 
    if (raiz == NULL)
    return raiz;
 
    raiz->h = 1 + max(getAltura(raiz->esq),
                           getAltura(raiz->dir));

    int dif = getFB(raiz);
 
    if (dif > 1 && getFB(raiz->esq) >= 0)
        return rotacaoDireita(raiz);
 
    if (dif > 1 && getFB(raiz->esq) < 0)
    {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }
 
    if (dif < -1 && getFB(raiz->dir) <= 0)
        return rotacaoEsquerda(raiz);
 
    if (dif < -1 && getFB(raiz->dir) > 0)
    {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }
 
    return raiz;
}

Noh* procurar(Noh* n, TC c) {
	if (n == nullptr || c == n->chave)
		return n;
	if (c < n->valor)
		return procurar(n->esq, c);
	else
		return procurar(n->dir, c);
}

Noh* procurar(DicAVL& D, TC c) {
	return procurar(D.raiz, c);
}

// void remover (DicAVL &D, Noh *n){

// }

// void terminar (DicAVL &D){

// }

int main() {
	
	DicAVL D;
	inicializar(D);

	inserir(D, 10, 1);
	// if(D.raiz->esq != nullptr)
	// {
	// 	cout << "Raiz: " << D.raiz->chave << '\n';
	// 	cout << "Filho esquerdo: " << D.raiz->esq->chave << '\n';
	// }
	// if(D.raiz->dir != nullptr)
	// {
	// 	cout << "Raiz: " << D.raiz->chave << '\n';
	// 	cout << "Filho direito: " << D.raiz->dir->chave << '\n';
	// }
	// cout << "Altura raiz: " << D.raiz->h << '\n';
	
	inserir(D, 5, 2);
	
	// if(D.raiz->esq != nullptr)
	// {
	// 	cout << "Raiz: " << D.raiz->chave << '\n';
	// 	cout << "Filho esquerdo: " << D.raiz->esq->chave << '\n';
	// }
	// if(D.raiz->dir != nullptr)
	// {
	// 	cout << "Raiz: " << D.raiz->chave << '\n';
	// 	cout << "Filho direito: " << D.raiz->dir->chave << '\n';
	// }
	// cout << "Altura raiz: " << D.raiz->h << '\n';
	
	inserir(D, 3, 3);
	
	// cout << "Chave: " << D.raiz->chave;
	// if(D.raiz->esq != nullptr){
	// 	cout << "Raiz: " << D.raiz->chave << '\n';
	// 	cout << "Filho esquerdo: " << D.raiz->esq->chave << '\n';
	// }
	// if(D.raiz->dir != nullptr)
	// {
	// 	cout << "Raiz: " << D.raiz->chave << '\n';
	// 	cout << "Filho direito: " << D.raiz->dir->chave << '\n';
	// }
	// cout << "Altura raiz: " << D.raiz->h << '\n';

	inserir(D, 7, 10);
	
	// if(D.raiz->esq != nullptr){
	// 	cout << "Raiz: " << D.raiz->chave << '\n';
	// 	cout << "Filho esquerdo: " << D.raiz->esq->chave << '\n';
	// }
	// if(D.raiz->dir != nullptr)
	// {
	// 	cout << "Raiz: " << D.raiz->chave << '\n';
	// 	cout << "Filho direito: " << D.raiz->dir->chave << '\n';
	// }
	// cout << "\nAltura raiz: " << D.raiz->h << '\n';

	inserir(D, 8, 10);

	// if(D.raiz->esq != nullptr)
	// {
	// 	cout << "Raiz: " << D.raiz->chave << '\n';
	// 	cout << "Filho esquerdo: " << D.raiz->esq->chave << '\n';
	// }
	// if(D.raiz->dir != nullptr)
	// {
	// 	cout << "Raiz: " << D.raiz->chave << '\n';
	// 	cout << "Filho direito: " << D.raiz->dir->chave << '\n';
	// }

	inserir(D, 11, 0);

	if(D.raiz->esq != nullptr)
	{
		cout << "Raiz: " << D.raiz->chave << '\n';
		cout << "Filho esquerdo: " << D.raiz->esq->chave << '\n';
	}
	if(D.raiz->dir != nullptr)
	{
		cout << "Raiz: " << D.raiz->chave << '\n';
		cout << "Filho direito: " << D.raiz->dir->chave << '\n';
	}

	deletar(D.raiz, 5);

	printArv(D.raiz);
}
