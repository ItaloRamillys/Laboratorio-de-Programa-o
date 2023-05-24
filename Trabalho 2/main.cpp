#include "instancias_Reais_Trabalho_2.hpp"
#include <chrono>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
using namespace chrono;

void forca_bruta(const char *P, const char *T, int *O) {
  
  int lengthP = strlen(P);
  int lengthT = strlen(T);

  int o = 0;

  for (int i = 0; i < lengthT; i++) {
    int ctrl = i;
    for (int j = 0; j < lengthP; j++) {

      if (T[ctrl + j] != P[j]) {
        break;
      }

      if (j == (lengthP - 1)) {
        O[o] = i;
        o++;
      }
    }
    if (i + 1 + lengthP > lengthT)
      break;
  }

  O[o] = -1;
}

void calculaPrefixo(const char *P, int *p) {

  int n = strlen(P);

  p[0] = -1;

  int l = -1;

  int i = 0;
  while (i < n - 1) {
    // cout << "\ni: " << i << " - l: " << l;
    // cout << "\nComparando: " << P[i+1] << " - " <<  P[l+1];
    if (P[i + 1] == P[l + 1]) {
      //cout << "\nS";
      l++;
      p[i + 1] = l;
      i++;
    } else {
      // cout << "\nN";
      if (l != -1) {
        // cout << "\nR" << l;
        l = p[l];
      } else {
        p[i + 1] = -1;
        i++;
      }
    }
  }
}

void kmp(const char *P, const char *T, int *O) {

  int count = 0;
  int k;
  int n = strlen(T);
  int m = strlen(P);

  // cout << "\nVia str(T): " << n;
  // cout << "\nVia str(P): " << m;

  // int tP = 0, tT = 0;
  // while (P[tP] != '\0')
  //   tP++;
  // while (T[tT] != '\0')
  //   tT++;
  // cout << "\nVia while(T): " << tT;
  // cout << "\nVia while(P): " << tP;

  int v[m];

  calculaPrefixo(P, v);
  // PARA VER O VETOR DE PREFIXOS, DESCOMENTE AS LINHAS ABAIXO
  // for (int i = 0; i < m; i++) {
  //   cout << v[i] << " > ";
  // }

  for (int p = 0; p < n; p++) {
    // cout << "\nPosicao no texto: " << p;
    for (int i = -1; i < m; i = i) {

      // cout << "\n >> " << T[p+i+1] << " - " << P[i+1];

      if (T[p + i + 1] == P[i + 1]) {
        //  cout << "\nMatch";
        if (i + 1 != m - 1) {
          //  cout << "\nContinue";
          i++;
          continue;
        } else {
          // cout << "\nFIND";
          // cout << '\n' << p << '\n';
          O[count] = p;
          k = v[i + 1];
          p = p + i + 1 - k;
          i = k;

          // cout << "\nP depois de encontrar: " << p << '\n';
          // cout << "\nK depois de encontrar: " << k << '\n';
          count++;
        }
      } else {
        // cout << "\nJUMP";
        //  cout << "\ni = " << i;
        if (i != -1) {
          k = v[i];
          p = p + i - k;
          i = k;
          // cout << "\n" << k;
          // cout << "\n" << i;
        } else {
          break;
        }
      }
    }
  }

  O[count] = -1;
}

void instancias_aleatorias(char l, int m, int n, int ia) {
  char letra_a = 'a';
  int num_a = letra_a;
  // cout << '\n' << "A: " << num_a;

  int x = l;
  // cout << '\n' << "X: " << x;

  int dif_letra = x - num_a;
  // cout << '\n' << "Dif: " << dif_letra;

  // default_random_engine randomGenerator(time(0));

  //GERANDO A SEMENTE APENAS UMA VEZ
  random_device randomDevice;
  mt19937 mtGenerator(randomDevice());
  uniform_int_distribution<int> dist2(0, dif_letra);

  // dist2(mtGenerator);
  char padrao[m + 1];
  char texto[n + 1];
  char caracter;

  int O[n + 1];

  double tempoKMP = 0;
  double tempoFB = 0;

  //ITERANDO PARA I INSTANCIAS
  for (int j = 0; j < ia; j++) {
    // cout << "\n-----------------------------------------------\n";
    // cout << "\n\nIteracao: " << j;
    for (int i = 0; i < m; i++) {
      caracter = num_a + dist2(mtGenerator);
      padrao[i] = caracter;
    }
    // cout << "\nPadrao gerado";
    for (int i = 0; i < n; i++) {
      caracter = num_a + dist2(mtGenerator);
      texto[i] = caracter;
    }
    // cout << "\nTexto gerado";

    // PARA VER O TEXTO E O PADRAO GERADOS, DESCOMENTE AS LINHAS ABAIXO
    // cout << "\nPadrao\n";

    // int i = 0;
    // for (i = 0; i < m; i++) {
    //   cout << padrao[i];
    // }
    // // padrao[i] = '\0';
    // cout << "\nTexto\n";

    // i = 0;
    // for (i = 0; i < n; i++) {
    //   cout << texto[i];
    // }
    // // texto[i] = '\0';

    // cout << '\n';

    auto inicio = steady_clock::now();
    // cout << "\nKMP:";
    kmp(padrao, texto, O);
    auto fim = steady_clock::now();
    auto elapsedKMP = std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio);

    // PARA VER OS INDICES NO TEXTO DO KMP, DESCOMENTE AS LINHAS ABAIXO
    // cout << "\n\nPadroes encontrados(KMP):\n";
    // int x = 0;
    // while (o[x] != -1) {
    //   cout << o[x] << "\n";
    //   x++;
    // }

    inicio = steady_clock::now();
    // cout << "\nFB:";
    forca_bruta(padrao, texto, O);
    fim = steady_clock::now();
    auto elapsedFB = std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio);

    // PARA VER OS INDICES NO TEXTO DO FB, DESCOMENTE AS LINHAS ABAIXO
    // cout << "\n\nPadroes encontrados(FP):\n";
    // x = 0;
    // while (o[x] != -1) {
    //   cout << o[x] << "\n";
    //   x++;
    // }

    tempoFB += elapsedFB.count() / 1e9;
    tempoKMP += elapsedKMP.count() / 1e9;
  }

  cout << "\nTempo KMP: " << tempoKMP;
  cout << "\nTempo FB: " << tempoFB;
}

void instancias_reais(int x, int y) {
  try {
    if (x >= 0 && y <= 35129 && x <= y) {
      int tamanho_texto = strlen(Texto_Livros);
      //POR SER UM TEXTO REAL NAO SERIA NECESSARIO ALOCAR UM ARRAY TAO GRANDE QUANTO O TEXTO
      int *O = new int[tamanho_texto+1];

      double tempoKMP = 0;
      double tempoFB = 0;

      for (int i = x; i < y; i++) {
        //Print nao entra no calculo do tempo
        //cout << "\nChamando para: " << Padroes_Palavras[i];
        auto inicio = steady_clock::now();

        kmp(Padroes_Palavras[i], Texto_Livros, O);

        auto fim = steady_clock::now();

        auto elapsedKMP = std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio);

        tempoKMP += elapsedKMP.count() / 1e9;

        inicio = steady_clock::now();

        forca_bruta(Padroes_Palavras[i], Texto_Livros, O);

        fim = steady_clock::now();

        auto elapsedFB = std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio);

        tempoFB += elapsedFB.count() / 1e9;
      }

      cout << "\nTempo para encontrar pelo forca_bruta: " << tempoFB;
      cout << "\nTempo para encontrar pelo kmp: " << tempoKMP;

      delete[] O;
    }
  } catch (exception &e) {
    cout << "Standard exception: " << e.what() << endl;
  }
}

int main(int argc, char *argv[]) {
  char tipo = *argv[1];

  if (tipo == 'A' && argc == 6) {
    char l = *argv[2];
    int m = atoi(argv[3]);
    int n = atoi(argv[4]);
    int i = atoi(argv[5]);
    instancias_aleatorias(l, m, n, i);
  } else if (tipo == 'R' && argc == 4) {
    int x = atoi(argv[2]);
    int y = atoi(argv[3]);
    instancias_reais(x, y);
  }

  return 0;
}
