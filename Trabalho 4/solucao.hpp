// -----------------------------------------------------------------------------
// Universidade Federal do CearÃ¡, Centro de CiÃªncias, Departamento de ComputaÃ§Ã£o
// Disciplina:  LaboratÃ³rio de ProgramaÃ§Ã£o - CK0215 2023.1 T01A
// Professor:   Pablo Mayckon Silva Farias
//
// Trabalho 4 - Interface para ImplementaÃ§Ã£o de DicionÃ¡rio baseado em Ãrvore AVL
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// IDENTIFICAÃ‡ÃƒO DO(A) ESTUDANTE:
//
// NOME: Italo Ramillys Benicio Silva
// MATRÃCULA: 399963
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Tudo o que estÃ¡ presente na interface abaixo deve ser mantido como estÃ¡,
// pois esta interface serÃ¡ utilizada no programa do professor para a realizaÃ§Ã£o
// dos testes.
//
// O trabalho consiste portanto em *completar* a implementaÃ§Ã£o abaixo,
// tornando-a funcional e atendendo aos requisitos deste trabalho.
//
// Os pontos a serem completados estÃ£o marcados com "TODO", isto Ã©, "por fazer".
// -----------------------------------------------------------------------------

#ifndef DICIOAVL_HPP
#define DICIOAVL_HPP

// -----------------------------------------------------------------------------

// A classe DicioAVL deve implementar um dicionÃ¡rio que associe chaves de tipo
// TC a valores de tipo TV.
//
// O dicionÃ¡rio deve organizar esses dados numa Ã¡rvore AVL em que os elementos
// sejam ordenados entre si a partir de suas chaves.
//
// Ã‰ pressuposto da classe que as chaves podem ser normalmente comparadas
// atravÃ©s dos operadores relacionais comuns: <, >=, !=, etc.

template <typename TC, typename TV>
class DicioAVL
{
public:
  // Numa implementaÃ§Ã£o tÃ­pica de dicionÃ¡rio,
  // a representaÃ§Ã£o interna normalmente fica inacessÃ­vel ao usuÃ¡rio;
  // neste trabalho, porÃ©m,
  // o professor precisa avaliar se a Ã¡rvore estÃ¡ correta,
  // e por isso a estrutura do nÃ³ Ã© exposta ao usuÃ¡rio (daÃ­ o "public" acima),
  // assim como o ponteiro raiz e a sentinela:

  struct Noh
  {
    TC chave;
    TV valor;
    Noh *pai, *esq, *dir;
    int altura;

    // VocÃª deve completar a estrutura do nÃ³ com:
    //
    // 1. Ponteiros para filho esquerdo, filho direito e pai.
    //
    // 2. Se necessÃ¡rio, algum campo adicional que viabilize a implementaÃ§Ã£o
    //    da Ã¡rvore AVL, como a altura do nÃ³, a informaÃ§Ã£o do balanceamento
    //    (-1, 0, +1), etc.
    //
    // VocÃª Ã© livre para escolher como vai representar esses elementos,
    // mas deve implementar as funÃ§Ãµes a seguir,
    // que permitirÃ£o que a estrutura da Ã¡rvore seja percorrida.
    // (quando o filho direito / filho esquerdo / pai nÃ£o existir,
    //  a respectiva funÃ§Ã£o deve retornar um ponteiro para "sent",
    //  declarada mais abaixo):

    // TODO: defina os campos restantes do nÃ³ da Ã¡rvore AVL.

    // -----------------------------------------------------------------------

    // Esta funÃ§Ã£o deve retornar um ponteiro para o filho direito,
    // se o nÃ³ possuir filho direito;
    // em caso contrÃ¡rio, deve ser retornado um ponteiro para o nÃ³ sentinela,
    // definido mais abaixo.

    // Noh* obter_dir ();  // Apague o ";" e escreva abaixo a implementaÃ§Ã£o.
    Noh *obter_dir()
    {
      if (dir != sent)
        return dir;
      return sent;
    }

    // -----------------------------------------------------------------------

    // Esta funÃ§Ã£o deve retornar um ponteiro para o filho esquerdo,
    // se o nÃ³ possuir filho esquerdo;
    // em caso contrÃ¡rio, deve ser retornado um ponteiro para o nÃ³ sentinela,
    // definido mais abaixo.

    // Noh* obter_esq ();
    Noh *obter_esq()
    {
      if (esq != sent)
        return esq;
      return sent;
    }

    // -----------------------------------------------------------------------

    // Esta funÃ§Ã£o deve retornar um ponteiro para o nÃ³ pai,
    // se o nÃ³ possuir nÃ³ pai;
    // em caso contrÃ¡rio, deve ser retornado um ponteiro para o nÃ³ sentinela,
    // definido mais abaixo.

    // Noh* obter_pai ();
    Noh *obter_pai()
    {
      if (pai != sent)
        return pai;
      return sent;
    }

  }; // struct Noh

  // --------------------------------------------------------------------------

  // Campos pÃºblicos de DicioAVL: raiz e sentinela.
  // Lembrete: nÃ£o altere-os, pois serÃ£o usados nos testes automÃ¡ticos.

  Noh sent;  // NÃ³ sentinela.
  Noh *raiz; // "raiz" deve apontar para "sent" quando a Ã¡rvore estiver vazia.

  // ==========================================================================

private:
  // VocÃª pode incluir campos e mÃ©todos que sejam relevantes para a
  // implementaÃ§Ã£o mas que fiquem inacessÃ­veis ao usuÃ¡rio da classe DicioAVL.

  // ==========================================================================

public:
  // Lembrete: tudo o que estÃ¡ abaixo em DicioAVL deve ser mantido pÃºblico e
  // inalterado, pois serÃ¡ utilizado nos testes do professor.
  //
  // Observe que isso nÃ£o impede que vocÃª inclua mÃ©todos que nÃ£o estejam
  // presentes abaixo; porÃ©m, analise se eles devem mesmo ser pÃºblicos.

  // --------------------------------------------------------------------------

  class Iterador
  {
  private:
    Noh *n;
    // Noh &sent;

    // VocÃª pode incluir campos e mÃ©todos que sejam relevantes para a
    // implementaÃ§Ã£o mas que fiquem inacessÃ­veis ao usuÃ¡rio de "Iterador".

    // TODO: Defina os campos da classe Iterador.

    // -----------------------------------------------------------------------

    // O comando abaixo permite que a classe DicioAVL enxergue os membros
    // privados desta classe Iterador.
    // Isso serÃ¡ particularmente Ãºtil no mÃ©todo "remover" de DicioAVL,
    // que recebe um iterador e precisa, a partir dele, acessar o nÃ³ a ser
    // removido.

    friend DicioAVL;

    // -----------------------------------------------------------------------

  public:
    // Lembrete: tudo o que estÃ¡ abaixo deve ser mantido pÃºblico em Iterador,
    // pois serÃ¡ utilizado nos testes do professor.
    //
    // Observe que isso nÃ£o impede que vocÃª inclua mÃ©todos que nÃ£o estejam
    // presentes abaixo.

    // -----------------------------------------------------------------------

    // Lembrete: Ã© possÃ­vel implementar diferentes construtores para uma mesma
    // classe.

    // Construtor padrÃ£o (sem argumentos): deve ser possÃ­vel inicializar um
    // iterador sem que ele aponte para algum elemento especÃ­fico de um
    // DicioAVL. Isso Ã© Ãºtil para declarar uma variÃ¡vel de tipo Iterador sem
    // ter a obrigaÃ§Ã£o de jÃ¡ apontÃ¡-la para um elemento de um dicionÃ¡rio.
    //
    // A Ãºnica operaÃ§Ã£o esperada sobre um iterador assim inicializado Ã©
    // receber uma cÃ³pia de outro iterador.
    // Portanto, nÃ£o se deve chamar mÃ©todos como "chave" nem operadores como
    // "==" e "++" sobre um iterador que nÃ£o esteja apontando para um elemento
    // de um dicionÃ¡rio.
    //
    // ObservaÃ§Ã£o: caso deseje, vocÃª pode implementar o construtor padrÃ£o de
    // forma que seja vÃ¡lido chamar os operadores "==" e "!=" sobre um
    // iterador assim inicializado. PorÃ©m, isso nÃ£o Ã© exigido neste trabalho.

    // Iterador ();
    Iterador() : n() {}
    Iterador(Noh *noh) : n(noh) {}

    // -----------------------------------------------------------------------

    // Os operadores "!=" e "==" abaixo podem ser chamados mesmo caso
    // o iterador esteja no "fim" do dicionÃ¡rio ("posiÃ§Ã£o" em que o iterador
    // nÃ£o se refere a nenhum elemento propriamente dito).

    // -----------------------------------------------------------------------

    // Este mÃ©todo deve retornar "true" se e somente se
    // o iterador atual e "j" NÃƒO SE REFEREM ao mesmo elemento ou posiÃ§Ã£o do
    // dicionÃ¡rio.

    // bool operator != (Iterador j)
    bool operator!=(Iterador j) { if(n == nullptr) return false; return n != j.n; }

    // -----------------------------------------------------------------------

    // Este mÃ©todo deve retornar "true" se e somente se
    // o iterador atual e "j" SE REFEREM ao mesmo elemento ou posiÃ§Ã£o do
    // dicionÃ¡rio.

    // bool operator == (Iterador j);
    bool operator==(Iterador j) { return n == j.n; }

    // -----------------------------------------------------------------------

    // Os mÃ©todos abaixo possuem como PRÃ‰-CONDIÃ‡ÃƒO o fato de que o iterador
    // aponta para um elemento propriamente dito do dicionÃ¡rio, ou seja,
    // que o iterador nÃ£o aponta para o "fim" do dicionÃ¡rio.
    //
    // Como para toda prÃ©-condiÃ§Ã£o, Ã© responsabilidade do usuÃ¡rio de Iterador
    // garantir que ela serÃ¡ satisfeita sempre que o mÃ©todo for chamado.
    //
    // Portanto, esses mÃ©todos NÃƒO PRECISAM TESTAR se o iterador aponta para o
    // "fim" do dicionÃ¡rio.

    // -----------------------------------------------------------------------

    // Este mÃ©todo deve retornar a "chave" do elemento apontado pelo iterador.

    // TC chave ();
    TC chave() { return n->chave; }

    // -----------------------------------------------------------------------

    // Este mÃ©todo deve retornar o "valor" do elemento apontado pelo iterador.

    // TV valor ();
    TV valor() { return n->valor; }

    // -----------------------------------------------------------------------

    // Este mÃ©todo deve fazer o iterador passar ao prÃ³ximo elemento do
    // dicionÃ¡rio, isto Ã©, ao elemento da CHAVE SUCESSORA, na ordem crescente
    // das chaves, se houver uma chave sucessora.
    //
    // Caso nÃ£o haja chave sucessora (ou seja, caso o iterador aponte para a
    // maior chave), o iterador deve passar a apontar para o "fim" do
    // dicionÃ¡rio.

    // Iterador& operator ++ ();
    Iterador &operator++()
    {
      cout << "\nRaiz ob: " << n->chave;
      // if (n->dir != nullptr)
      // {
      //   n = n->dir;
      //   while (n->esq != nullptr) {
      //     n = n->esq;
      //   }
      //   return *this;
      // }

      // cout << "\nComparando: " << n->pai->chave << " - " << n->chave;
      // Noh *paiN = n->pai;

      // if(paiN->chave <= n->chave)
      // {
      //   while(paiN != nullptr && n == paiN->dir)
      //     n = paiN->pai;

      //   return *this;
      // }else
      // {
      //   n = n->dir;
      //   return *this;
      // }

      Noh *p;
      if (n->dir != nullptr)
      {
        n = n->dir;

        while (n->esq != nullptr)
        {
          n = n->esq;
        }
      }
      else
      {
        p = n->pai;
        while (p != nullptr && n == p->dir)
        {
          n = p;
          p = p->pai;
        }

        n = p;
      }
      return *this;
    }

  }; // class Iterador

  // --------------------------------------------------------------------------

  // MÃ©todos pÃºblicos de DicioAVL:

  // --------------------------------------------------------------------------

  // Construtor: deve inicializar o dicionÃ¡rio como vazio.

  // DicioAVL ()
  DicioAVL()
  {
    sent.chave = -1;
    sent.valor = -1;
    sent.dir = sent.esq = &sent;
    sent.altura = 0;
    // raiz = &sent;
    raiz = nullptr;
  }
  DicioAVL(Noh sent, Noh *raiz) : raiz(raiz), sent(sent) {}

  // --------------------------------------------------------------------------

  // Destrutor: deve desalocar toda a memÃ³ria dinamicamente alocada pelo
  // dicionÃ¡rio (no caso, basicamente a Ã¡rvore AVL).

  //~DicioAVL ();
  ~DicioAVL()
  {
  }
  //  {
  //  // TODO
  //  }

  // --------------------------------------------------------------------------

  // Este mÃ©todo deve retornar um iterador apontando para o elemento de menor
  // chave, caso exista um.
  // Se o dicionÃ¡rio estiver vazio, deve retornar um iterador para o "fim".

  Iterador begin()
  {
    Noh *aux = raiz;
    while (true)
    {
      // if (aux->esq == &sent)
      if (aux->esq == nullptr)
        return Iterador(aux);
      aux = aux->esq;
    }
  }

  // --------------------------------------------------------------------------

  // Deve retornar um iterador num estado especial, que seja diferente do
  // estado de um iterador que aponte para um elemento propriamente dito,
  // e que dessa forma sirva para caracterizar a situaÃ§Ã£o em que o iterador
  // tenha atingido o "fim" do dicionÃ¡rio.

  // Iterador end ();
  Iterador end()
  {
    Noh *aux = raiz;
    while (true)
    {
      // if (aux->dir == &sent)
      if (aux->dir == nullptr)
        return Iterador(aux->dir);
      aux = aux->dir;
    }
  }

  // --------------------------------------------------------------------------

  // Este mÃ©todo deve inserir a chave "c" e o valor "v" no dicionÃ¡rio, partindo
  // da PRÃ‰-CONDIÃ‡ÃƒO de que a chave "c" nÃ£o estÃ¡ presente no dicionÃ¡rio,
  // ou seja, a funÃ§Ã£o nÃ£o precisa nem deve fazer esse teste.
  //
  // Em caso de falha de alocaÃ§Ã£o de memÃ³ria,
  // o mÃ©todo deve jogar uma exceÃ§Ã£o do tipo std::bad_alloc
  // (que jÃ¡ Ã© aquele jogada pelo operador "new" em caso de falha de alocaÃ§Ã£o).
  //
  // A funÃ§Ã£o deve retornar um iterador apontando para o elemento inserido.
  //
  // ATENÃ‡ÃƒO: o iterador retornado deve continuar vÃ¡lido e relativo ao par
  // -------  (c,v) enquanto esse par nÃ£o for removido do dicionÃ¡rio.
  //
  // A observaÃ§Ã£o acima Ã© particularmente importante para o caso da REMOÃ‡ÃƒO
  // em que o nÃ³ do par a ser removido possui dois filhos. Nesse caso, nÃ£o
  // basta apenas copiar os campos do nÃ³ sucessor para o nÃ³ em questÃ£o, pois
  // isso faria com que o par sucessor mudasse de nÃ³, invalidando algum
  // iterador relativo a esse par; portanto, nesse caso da remoÃ§Ã£o, Ã©
  // necessÃ¡rio que o nÃ³ do sucessor realmente ocupe o lugar da Ã¡rvore que
  // estava sendo ocupado pelo nÃ³ a ser removido.

  int max(int a, int b)
  {
    return (a > b) ? a : b;
  }
  int getAltura(Noh *n)
  {
    if (n == nullptr)
      return 0;
    else
      return n->altura;
  }
  int getBalanceamento(Noh *n) // Fator de difamento
  {
    if (n == nullptr)
      return 0;
    else
      return (getAltura(n->esq) - getAltura(n->dir));
  }

  void printNoh(Noh *x)
  {
    cout << "\n"
         << x->chave << " : " << x->valor;

    cout << " | PAI: ";
    if (x->pai != nullptr)
      cout << x->pai->chave;
    else
      cout << "NULO";

    cout << " | ESQ: ";
    if (x->esq != nullptr)
      cout << x->esq->chave;
    else
      cout << "NULO";

    cout << " | DIR: ";
    if (x->dir != nullptr)
      cout << x->dir->chave;
    else
      cout << "NULO";
    cout << " | Altura: " << raiz->altura;
  }

  Noh *rotacaoDireita(Noh *y)
  {
    cout << "\nRotacao em[D]: " << y->chave;
    Noh *ey = y->esq;
    ey->pai = y->pai;
    Noh *dy = ey->dir;
    Noh *paiY = y->pai;
    if (paiY != nullptr)
    {
      ey->pai = paiY;
      paiY->esq = ey;
    }

    Noh *dey = ey->dir;
    if (dey != nullptr)
      dey->pai = y;

    ey->dir = y;
    y->esq = dy;
    y->pai = ey;

    y->altura = max(getAltura(y->esq), getAltura(y->dir)) + 1;
    ey->altura = max(getAltura(ey->esq), getAltura(ey->dir)) + 1;

    printNoh(ey);
    return ey;
  }

  Noh *rotacaoEsquerda(Noh *y)
  {
    cout << "\nRotacao em[E]: " << y->chave;
    Noh *dy = y->dir;
    dy->pai = y->pai;
    Noh *ey = dy->esq;
    Noh *paiY = y->pai;
    if (paiY != nullptr)
    {
      dy->pai = paiY;
      paiY->dir = dy;
    }

    Noh *edy = dy->esq;
    if (edy != nullptr)
      edy->pai = y;

    dy->esq = y;
    y->dir = ey;
    y->pai = dy;

    y->altura = max(getAltura(y->esq), getAltura(y->dir)) + 1;
    dy->altura = max(getAltura(dy->esq), getAltura(dy->dir)) + 1;

    return dy;
  }

  void printArv(Noh *raiz)
  {
    if (raiz != nullptr && raiz != &sent)
    {
      cout << '\n'
           << raiz->chave;
      if (raiz->pai != nullptr && raiz->pai != &sent)
        cout << " | Pai: " << raiz->pai->chave;
      else
        cout << " | Pai: -";
      if (raiz->esq != nullptr && raiz->esq != &sent)
        cout << " | Esq: " << raiz->esq->chave;
      else
        cout << " | Esq: -";
      if (raiz->dir != nullptr && raiz->dir != &sent)
        cout << " | Dir: " << raiz->dir->chave;
      else
        cout << " | Dir: -";
      cout << " | Altura: " << raiz->altura;
      printArv(raiz->esq);
      printArv(raiz->dir);
    }
  }

  Iterador inserir(TC c, TV v)
  {
    cout << "\nInserir\nChave:" << c << "\nValor:" << v;
    Noh *n = new Noh;
    n->esq = n->dir = nullptr;
    // n->esq = n->dir = &sent;
    n->chave = c;
    n->valor = v;
    n->altura = 1;
    n->pai = nullptr;

    Noh *aux = raiz;

    // if (raiz == &sent)
    if (raiz == nullptr)
    {
      cout << "\nInserindo na arvore vazia";
      raiz = n;
      Iterador i(n);
      return i;
    }

    cout << "\nRaiz atual:" << raiz->chave;

    cout << '\n';

    while (aux != nullptr && aux != &sent)
    {
      cout << "\nIterador: " << aux->valor << endl;
      if (c < aux->chave)
      {
        cout << c << " < " << aux->chave << " - e";
        // printNoh(aux);
        if (aux->esq != nullptr && aux->esq != &sent)
        {
          aux = aux->esq;
          cout << "\nIndo pro noh[E]: " << aux->valor;
        }
        else
        {
          n->pai = aux;
          aux->esq = n;

          break;
        }
        // aux = aux->esq;
      }
      else if (c > aux->chave)
      {
        cout << c << " > " << aux->chave << " - d";
        // printNoh(aux);

        if (aux->dir != nullptr && aux->dir != &sent)
        {
          aux = aux->dir;
          cout << "\nIndo pro noh[D]: " << aux->valor;
        }
        else
        {
          n->pai = aux;
          aux->dir = n;

          break;
        }
        // aux = aux->dir;
      }
    }

    // aux = n;
    //  else{
    //    return nullptr;
    //    cout << "\nChave duplicada \n";
    //  }
    cout << "\n--------------------------\n";
    cout << "Back";

    Noh *nohRet = n;
    while (n != nullptr && n != &sent)
    {
      cout << "\nChamada noh:\n";
      printNoh(n);
      // if(n == nullptr) break;
      // n->altura = n->altura + 1;

      cout << "\nAlturas: " << getAltura(n->esq) << " - " << getAltura(n->dir);
      n->altura = 1 + max(getAltura(n->esq), getAltura(n->dir));
      // cout << "\nMax: " << max(getAltura(raiz->esq), getAltura(raiz->dir));

      // cout << "\nALtura atual: " << raiz->altura;
      int dif = getBalanceamento(n);
      cout << "\nDif: " << dif << ' ';

      if (dif < -1 && n->dir != nullptr && c > n->dir->chave)
      {
        cout << "\nRotacao Esq NEGATIVO";
        // Verificar aqui se o noh é a raiz geral da arvore
        if (n == raiz)
          raiz = rotacaoEsquerda(n);
        else
          rotacaoEsquerda(n);
      }

      if (dif < -1 && n->dir != nullptr && c < n->dir->chave)
      {
        cout << "\nRotacao Dir NEGATIVO";
        raiz->dir = rotacaoDireita(n->dir);
        if (n == raiz)
          raiz = rotacaoEsquerda(n);
        else
          rotacaoEsquerda(n);
      }

      if (dif > 1 && n->esq != nullptr && c < n->esq->chave)
      {
        cout << "\nRotacao Dir POSITIVO";
        if (n == raiz)
          raiz = rotacaoDireita(n);
        else
          rotacaoDireita(n);
      }
      if (dif > 1 && n->esq != nullptr && c > n->esq->chave)
      {
        cout << "\nRotacao Esq POSITIVO";
        raiz->esq = rotacaoEsquerda(n->esq);
        if (n == raiz)
          raiz = rotacaoDireita(n);
        else
          rotacaoDireita(n);
      }

      n = n->pai;
    }

    cout << "\nRaiz: " << raiz->chave;
    cout << "\nAltura da raiz: " << raiz->altura;
    printArv(raiz);
    Iterador i(nohRet);
    // raiz = n;
    return i;
  }

  // --------------------------------------------------------------------------

  // Deve retornar um iterador apontando para o elemento de chave "c",
  // caso essa chave esteja presente no dicionÃ¡rio.
  // Se a chave nÃ£o estiver presente, deve retornar um iterador para o "fim".

  Iterador buscar(TC c)
  {
    // while (raiz != nullptr)
    // {
    //   if (raiz->chave == c)
    //   {
    //     cout << "Achei";
    //     Iterador i(raiz);
    //     return i;
    //   }
    //   if (c < raiz->chave)
    //   {
    //     cout << "\nEsq";
    //     raiz = raiz->esq;
    //   }
    //   else
    //   {
    //     cout << "\nDir";
    //     raiz = raiz->dir;
    //   }
    // }
    
    // Iterador i(nullptr);
    // return i;
    // If raiz is NULL
    Noh *raizAux = raiz;

    // Recur to the left subtree if
    // the current node's value is
    // greater than key
    while(true)
    {
      cout << "\nRaiz busca: " << raizAux->chave;
      if(raizAux->chave == c)
        break;
      if (raizAux->chave > c) {
        raizAux = raizAux->esq;
      }else{
        raizAux = raizAux->dir;
      }
    }
    Iterador i(raizAux);
    return i;
  }

  // --------------------------------------------------------------------------

  // Este mÃ©todo deve remover do dicionÃ¡rio o elemento apontado pelo iterador
  // recebido, caso o iterador aponte para um elemento do dicionÃ¡rio.
  //
  // Ã‰ PRÃ‰-CONDIÃ‡ÃƒO da funÃ§Ã£o que o iterador recebido estarÃ¡ apontando
  // para algum elemento ou para o "fim" do dicionÃ¡rio.
  //
  // Se o iterador apontar para o "fim" do dicionÃ¡rio,
  // a funÃ§Ã£o deve simplesmente deixar o dicionÃ¡rio inalterado.

  void remover(Iterador i)
  {
    
     
    // STEP 1: PERFORM STANDARD BST DELETE
    if (raiz == NULL)
        return raiz;
 
    // If the chave to be deleted is smaller
    // than the raiz's chave, then it lies
    // in esq subtree
    if ( n->chave < raiz->chave )
        raiz->esq = deleteNoh(raiz->esq, chave);
 
    // If the chave to be deleted is greater
    // than the raiz's chave, then it lies
    // in dir subtree
    else if( n-> > raiz->chave )
        raiz->dir = deleteNoh(raiz->dir, chave);
 
    // if chave is same as raiz's chave, then
    // This is the Noh to be deleted
    else
    {
        // Noh with only one child or no child
        if( (raiz->esq == NULL) ||
            (raiz->dir == NULL) )
        {
            Noh *temp = raiz->esq ?
                         raiz->esq :
                         raiz->dir;
 
            // No child case
            if (temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else // One child case
            *raiz = *temp; // Copy the contents of
                           // the non-empty child
            free(temp);
        }
        else
        {
            // Noh with two children: Get the inorder
            // successor (smallest in the dir subtree)
            Noh* temp = minValueNoh(raiz->dir);
 
            // Copy the inorder successor's
            // data to this Noh
            raiz->chave = temp->chave;
 
            // Delete the inorder successor
            raiz->dir = deleteNoh(raiz->dir,
                                     temp->chave);
        }
    }
 
    if (raiz == NULL)
      return raiz;
 
    // STEP 2: UPDATE h OF THE CURRENT Noh
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

}; // class DicioAVL

// -----------------------------------------------------------------------------

#endif