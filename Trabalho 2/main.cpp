#include <iostream>
#include <stdio.h>
#include <iomanip>  
#include <stdlib.h>
#include <chrono>
#include <random>
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;
using namespace chrono;

void forca_bruta (const char *P, const char *T, int *O)
{
    // cout << "\nPadrao: " << P << "\n";
    // cout << "\nTexto: " << T << "\n";

    int lengthP = strlen(P);
    int lengthT = strlen(T);

    // cout << "\nTamanho Padrao: " << lengthP << "\n";
    // cout << "\nTamanho Texto: " << lengthT << "\n";

    int o = 0;

    for(int i = 0; i < lengthT; i++)
    {
        int ctrl = i;
        for(int j = 0; j < lengthP; j++)
        {
            
            // cout << "\n--------------------------------------------";
            // cout << "\nLetra " << ctrl + j << " do texto";
            // cout << "\nLetra " << j << " do padrao";
            if(T[ctrl + j] != P[j])
            {
                // cout << "\nNao deu match " << T[ctrl + j] << " com " << P[j];
                break;
            }     
            //cout << "\nDeu match " << T[ctrl + j] << " com " << P[j];

            if(j == (lengthP-1))
            {
                //cout << "\nEncontrei 1 vez em: " << i << "\n";
                O[o] = i;
                o++;
            }
        }
        if(i + 1 + lengthP > lengthT)
            break;
    }
    //cout << "POsicao: " << o;
    O[o] = -1; 

    // cout << "\n\nPadroes encontrados:\n\n";
    // for(int i = 0; i <= o; i++)
    // {
    //     cout << O[i] << "\n";
    // }
}

int* calculaPrefixo(const char *P, int* p)
{

    int n = strlen(P);

    p[0] = -1;

    // cout << "\nTamanho de P: " << n;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // cout << "\nComparando: " << P[i] << " - " << P[j];
            if(P[j] == P[i])
            {
                // cout << "\nAnda os dois";
                p[i] = p[i-1]+1;
                i++;
            }else if(P[j] != P[i] && j > 0)
            {
                
                // cout << "\nAnda para: " << i + p[j-1];
                p[i] = -1;
                i = i + p[j-1];
                
                break;
            }else{
                p[i] = -1;
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        // cout << "\n-" << p[i] << "-";
    }

    return p;
}

void kmp (const char *P, const char *T, int *O)
{
    int count = 0;
    int k;
    int n = strlen(T);
    int m = strlen(P);
    int v[m];
    calculaPrefixo(P, v);
    // cout << "\n\nVetor: "<< m << "\n\n";
    
    for (int p = 0; p < n; p++) {
        // cout << "\nPosicao no texto: " << p;
        for (int i = -1; i < m; i = i) {

            // cout << "\nComparando: " << T[p+i+1] << " - " << P[i+1];

            if(T[p+i+1] == P[i+1])
            {
                // cout << "\nMatch";
                if(i+1 != m-1){
                    // cout << "\nContinue";
                    i++;
                    continue;
                }
                else
                {
                    // cout << "\nAinda tem padrao";
                    O[count] = p;
                    k = v[i+1];
                    p = p + i + 1 - k;
                    i = k;
                    count++;
                }
            }else
            {   
                // cout << "\nNo match";
                // cout << "\ni = " << i;
                if(i != -1)
                {
                    k = v[i];
                    p = p + i - k;
                    i = k;
                    // cout << "\n" << k;
                    // cout << "\n" << i;
                }else
                {
                    break;
                }
            }
        }
    }

    O[count] = -1;
}

//int main(int argc, char *argv[]) {
int main(){    
    //char *padrao = argv[argc-1];
    //char *texto = argv[argc-2];

    const char texto[20118] = "Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate). Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99, considera-se o fato de seus dados já estarem cadastrados em um banco de dados 99, e que ele teria de fazer alguma validação para prosseguir com seu cadastro. Levando esses fatos em consideração, necessita-se de um endpoint em que espere a chave do usuário (cpf), o serviço que ele vai solicitar (typeService), e sua placa de veículo (vehicleLicensePlate).";
    char padrao[] = "Com base na informação de que o motorista apenas pode se cadastrar na campanha kit gás se ele for motorista 99";

    int o[100]; 
    
    auto inicio = steady_clock::now();

    forca_bruta(padrao, texto, o);

    auto fim = steady_clock::now();
    auto elapsedFB = std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio);
    
    cout << "\nPadrao encontrado em(FB): ";
    int i = 0;
    while (o[i] != -1) 
    {
        cout << "\n" << o[i];
        i++;
    }

    int p[100]; 
    inicio = steady_clock::now();

    kmp(padrao, texto, p);

    fim = steady_clock::now();
    auto elapsedKMP = std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio);
    
    cout << "\nPadrao encontrado em(KMP): ";
    i = 0;
    while (p[i] != -1) 
    {
        cout << "\n" << p[i];
        i++;
    }

    float a = elapsedFB.count()/1e9;

    float b = elapsedKMP.count()/1e9;

    cout << "\n\nTempo forca_bruta: "  << std::setprecision(51) << std::fixed << a << "\n" ;
    cout << "\n\nTempo kmp: "  << std::setprecision(51) << std::fixed << b << "\n" ;

	return 0;
   
}
