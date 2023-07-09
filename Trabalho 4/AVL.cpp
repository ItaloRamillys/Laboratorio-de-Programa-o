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
Noh* rotacaoDireita(Noh* y)
{
	cout << "Rotacao em: " << y->chave;
	Noh* x = y->esq;
	Noh* dx = x->dir;

	x->dir = y;
	y->esq = dx;

	y->h = max(getAltura(y->esq), getAltura(y->dir)) + 1;
	x->h = max(getAltura(x->esq), getAltura(x->dir)) + 1;
	return x;
}

Noh* rotacaoEsquerda(Noh* y)
{
	Noh* x = y->dir;
	Noh* ex = x->esq;

	x->esq = y;
	y->dir = ex;

	y->h = max(getAltura(y->esq), getAltura(y->dir)) + 1;
	x->h = max(getAltura(x->esq), getAltura(x->dir)) + 1;

	return x;
}

// Fim


void inicializar(DicAVL& D) {
	D.raiz = nullptr;
}

Noh* inserir(Noh* n, TC c, TV v) {
	cout << "\nInserindo\nChave:"<<c<<"\nValor:"<<v<<"\n";
	if (n == nullptr) {
		Noh *n = new Noh;
		n->esq = n->dir = nullptr;
		n->chave = c;
		n->valor = v;
		n->h = 1;
		return n;
		cout << "\nInserindo na folha";
	}

	cout << '\n';
	if (c < n->chave) 
	{
		cout << c << " < " << n->chave << " - e";
		n->esq = inserir(n->esq, c, v);
	}
	else if (c > n->chave) 
	{
		cout << c << " < " << n->chave << " - d";
		n->dir = inserir(n->dir, c, v);
	}
	else{
		return nullptr;
		cout << "\nChave duplicada \n";
	}
	cout << "Raiz observada: " << n->chave;
	n->h = 1 + max(getAltura(n->esq), getAltura(n->dir));

	int dif = getFB(n);

	cout << "\nDif: " << dif << ' ';

	if (dif < -1 && c > n->dir->chave)
		return rotacaoEsquerda(n);
	if (dif < -1 && c < n->dir->chave) {
		n->dir = rotacaoDireita(n->dir);
		return rotacaoEsquerda(n);
	}
	
	if (dif > 1 && c < n->esq->chave)
	{
		cout <<"\nRotacao Dir";
		return rotacaoDireita(n);
	}
	if (dif > 1 && c > n->esq->chave) {
		cout <<"\nRotacao Esq";
		n->esq = rotacaoEsquerda(n);
		return rotacaoDireita(n);
	}

	return n;
}

Noh* inserir(DicAVL& D, TC c, TV v) {
	if (D.raiz == nullptr)
		return D.raiz = inserir(D.raiz, c, v);
	else
		return D.raiz = inserir(D.raiz, c, v);
}

Noh* deleteNode(Node* root, int chave)
{
     
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;
 
    // If the chave to be deleted is smaller
    // than the root's chave, then it lies
    // in esq subtree
    if ( chave < root->chave )
        root->esq = deleteNode(root->esq, chave);
 
    // If the chave to be deleted is greater
    // than the root's chave, then it lies
    // in dir subtree
    else if( chave > root->chave )
        root->dir = deleteNode(root->dir, chave);
 
    // if chave is same as root's chave, then
    // This is the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->esq == NULL) ||
            (root->dir == NULL) )
        {
            Node *temp = root->esq ?
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
            // node with two children: Get the inorder
            // successor (smallest in the dir subtree)
            Node* temp = minValueNode(root->dir);
 
            // Copy the inorder successor's
            // data to this node
            root->chave = temp->chave;
 
            // Delete the inorder successor
            root->dir = deleteNode(root->dir,
                                     temp->chave);
        }
    }
 
    // If the tree had only one node
    // then return
    if (root == NULL)
    return root;
 
    // STEP 2: UPDATE h OF THE CURRENT NODE
    root->h = 1 + max(h(root->esq),
                           h(root->dir));
 
    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    int balance = getBalance(root);
 
    // If this node becomes unbalanced,
    // then there are 4 cases
 
    // esq esq Case
    if (balance > 1 &&
        getBalance(root->esq) >= 0)
        return dirRotate(root);
 
    // esq dir Case
    if (balance > 1 &&
        getBalance(root->esq) < 0)
    {
        root->esq = esqRotate(root->esq);
        return dirRotate(root);
    }
 
    // dir dir Case
    if (balance < -1 &&
        getBalance(root->dir) <= 0)
        return esqRotate(root);
 
    // dir esq Case
    if (balance < -1 &&
        getBalance(root->dir) > 0)
    {
        root->dir = dirRotate(root->dir);
        return esqRotate(root);
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

	inserir(D, 10, 1);
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
	inserir(D, 5, 2);
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
	inserir(D, 7, 10);
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
	inserir(D, 8, 10);
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
}
