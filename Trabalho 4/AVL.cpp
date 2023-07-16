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

void preOrder(Noh *root)
{
    if(root != nullptr)
    {

        cout <<'\n'<< root->chave;
		if( root->esq != nullptr )
			cout << " | Esq: " << root->esq->chave;
		else
			cout << " | Esq: NULO";
		if( root->dir != nullptr )
			cout << " | Dir: " << root->dir->chave;
		else
			cout << " | Dir: NULO";
        preOrder(root->esq);
        preOrder(root->dir);
    }
}

Noh * minValueNoh(Noh* no)
{
    Noh* current = no;
 
    /* loop down to find the leftmost leaf */
    while (current->esq != NULL)
        current = current->esq;
 
    return current;
}


Noh* deleteNoh(Noh* root, int chave)
{
     
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;
 
    // If the chave to be deleted is smaller
    // than the root's chave, then it lies
    // in esq subtree
    if ( chave < root->chave )
        root->esq = deleteNoh(root->esq, chave);
 
    // If the chave to be deleted is greater
    // than the root's chave, then it lies
    // in dir subtree
    else if( chave > root->chave )
        root->dir = deleteNoh(root->dir, chave);
 
    // if chave is same as root's chave, then
    // This is the Noh to be deleted
    else
    {
        // Noh with only one child or no child
        if( (root->esq == NULL) ||
            (root->dir == NULL) )
        {
            Noh *temp = root->esq ?
                         root->esq :
                         root->dir;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp; // Copy the contents of
                           // the non-empty child
            free(temp);
        }
        else
        {
            // Noh with two children: Get the inorder
            // successor (smallest in the dir subtree)
            Noh* temp = minValueNoh(root->dir);
 
            // Copy the inorder successor's
            // data to this Noh
            root->chave = temp->chave;
 
            // Delete the inorder successor
            root->dir = deleteNoh(root->dir,
                                     temp->chave);
        }
    }
 
    // If the tree had only one Noh
    // then return
    if (root == NULL)
    return root;
 
    // STEP 2: UPDATE h OF THE CURRENT Noh
    root->h = 1 + max(getAltura(root->esq),
                           getAltura(root->dir));
 
    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS Noh (to check whether this
    // Noh became unbalanced)
    int balance = getFB(root);
 
    // If this Noh becomes unbalanced,
    // then there are 4 cases
 
    // esq esq Case
    if (balance > 1 &&
        getFB(root->esq) >= 0)
        return rotacaoDireita(root);
 
    // esq dir Case
    if (balance > 1 &&
        getFB(root->esq) < 0)
    {
        root->esq = rotacaoEsquerda(root->esq);
        return rotacaoDireita(root);
    }
 
    // dir dir Case
    if (balance < -1 &&
        getFB(root->dir) <= 0)
        return rotacaoEsquerda(root);
 
    // dir esq Case
    if (balance < -1 &&
        getFB(root->dir) > 0)
    {
        root->dir = rotacaoDireita(root->dir);
        return rotacaoEsquerda(root);
    }
 
    return root;
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