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
int getFB(Noh* n) // Fator de balanceamento
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
		n->pai = lp;
		n->esq = n->dir = nullptr;
		n->chave = c;
		n->valor = v;
		n->h = 1;
		return n;
	}

	cout << '\n';
	if (c < n->chave) 
	{
		cout << c << " < " << n->chave << " - e";
		n->esq = inserir(n->esq, n, c, v);
	}
	else if (c > n->chave) 
	{
		cout << c << " < " << n->chave << " - d";
		n->dir = inserir(n->dir, n, c, v);
	}
	else{
		return nullptr;
		cout << "\nChave duplicada \n";
	}
	cout << "\nRaiz observada: " << n->chave;
	n->h = 1 + max(getAltura(n->esq), getAltura(n->dir));

	int dif = getFB(n);

	cout << "\nDif: " << dif << ' ';

	if (dif < -1 && c > n->dir->chave)
	{
		cout <<"\nRotacao Esq NEGATIVO";
		return rotacaoEsquerda(n);
	}
	if (dif < -1 && c < n->dir->chave) {
		cout <<"\nRotacao Dir NEGATIVO";
		n->dir = rotacaoDireita(n->dir);
		return rotacaoEsquerda(n);
	}
	
	if (dif > 1 && c < n->esq->chave)
	{
		cout <<"\nRotacao Dir POSITIVO";
		return rotacaoDireita(n);
	}
	if (dif > 1 && c > n->esq->chave) {
		cout <<"\nRotacao Esq POSITIVO";
		n->esq = rotacaoEsquerda(n->esq);
		return rotacaoDireita(n);
	}

	return n;
}

Noh* inserir(DicAVL& D, TC c, TV v) {
	if (D.raiz == nullptr)
		return D.raiz = inserir(D.raiz,D.raiz, c, v);
	else
		return D.raiz = inserir(D.raiz,D.raiz, c, v);
}

void preOrder(Noh *raiz)
{
    if(raiz != nullptr)
    {

        cout <<'\n'<< raiz->chave;
		if( raiz->esq != nullptr )
			cout << " | Esq: " << raiz->esq->chave;
		else
			cout << " | Esq: NULO";
		if( raiz->dir != nullptr )
			cout << " | Dir: " << raiz->dir->chave;
		else
			cout << " | Dir: NULO";
        preOrder(raiz->esq);
        preOrder(raiz->dir);
    }
}

Noh * getMinNoh(Noh* no)
{
    Noh* aux = no;
 
    while (aux->esq != NULL)
        aux = aux->esq;
 
    return aux;
}


Noh* deleteNoh(Noh* raiz, int chave)
{
     
    // STEP 1: PERFORM STANDARD BST DELETE
    if (raiz == NULL)
        return raiz;
 
    // If the chave to be deleted is smaller
    // than the raiz's chave, then it lies
    // in esq subtree
    if ( chave < raiz->chave )
        raiz->esq = deleteNoh(raiz->esq, chave);
 
    // If the chave to be deleted is greater
    // than the raiz's chave, then it lies
    // in dir subtree
    else if( chave > raiz->chave )
        raiz->dir = deleteNoh(raiz->dir, chave);
 
    // if chave is same as raiz's chave, then
    // This is the Noh to be deleted
    else
    {
        // Noh with only one child or no child
        if( (raiz->esq == NULL) ||
            (raiz->dir == NULL) )
        {
            Noh *aux = raiz->esq ?
                         raiz->esq :
                         raiz->dir;
 
            // No child case
            if (aux == NULL)
            {
                aux = raiz;
                raiz = NULL;
            }
            else // One child case
            *raiz = *aux; // Copy the contents of
                           // the non-empty child
            free(aux);
        }
        else
        {
            // Noh with two children: Get the inorder
            // successor (smallest in the dir subtree)
            Noh* aux = getMinNoh(raiz->dir);
 
            // Copy the inorder successor's
            // data to this Noh
            raiz->chave = aux->chave;
 
            // Delete the inorder successor
            raiz->dir = deleteNoh(raiz->dir,
                                     aux->chave);
        }
    }
 
    // If the tree had only one Noh
    // then return
    if (raiz == NULL)
    return raiz;
 
    // STEP 2: UPDATE h OF THE aux Noh
    raiz->h = 1 + max(getAltura(raiz->esq),
                           getAltura(raiz->dir));
 
    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS Noh (to check whether this
    // Noh became unbalanced)
    int balance = getFB(raiz);
 
    // If this Noh becomes unbalanced,
    // then there are 4 cases
 
    // esq esq Case
    if (balance > 1 &&
        getFB(raiz->esq) >= 0)
        return rotacaoDireita(raiz);
 
    // esq dir Case
    if (balance > 1 &&
        getFB(raiz->esq) < 0)
    {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }
 
    // dir dir Case
    if (balance < -1 &&
        getFB(raiz->dir) <= 0)
        return rotacaoEsquerda(raiz);
 
    // dir esq Case
    if (balance < -1 &&
        getFB(raiz->dir) > 0)
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

	inserir(D, 1, 1);
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
		cout << "Altura raiz: " << D.raiz->h << '\n';
	inserir(D, 2, 2);
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
		cout << "Altura raiz: " << D.raiz->h << '\n';
	inserir(D, 3, 3);
	cout << "Chave: " << D.raiz->chave;
	if(D.raiz->esq != nullptr){
		cout << "Raiz: " << D.raiz->chave << '\n';
		cout << "Filho esquerdo: " << D.raiz->esq->chave << '\n';
	}
	if(D.raiz->dir != nullptr)
	{
		cout << "Raiz: " << D.raiz->chave << '\n';
		cout << "Filho direito: " << D.raiz->dir->chave << '\n';
	}
		cout << "Altura raiz: " << D.raiz->h << '\n';
	inserir(D, 4, 10);
	if(D.raiz->esq != nullptr){
		cout << "Raiz: " << D.raiz->chave << '\n';
		cout << "Filho esquerdo: " << D.raiz->esq->chave << '\n';
	}
	if(D.raiz->dir != nullptr)
	{
		cout << "Raiz: " << D.raiz->chave << '\n';
		cout << "Filho direito: " << D.raiz->dir->chave << '\n';
	}
	cout << "\nAltura raiz: " << D.raiz->h << '\n';

	inserir(D, 5, 10);

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

	inserir(D, 6, 0);

	preOrder(D.raiz);
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

	deleteNoh(D.raiz, 5);

	preOrder(D.raiz);
}