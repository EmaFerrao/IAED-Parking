/**
 * Define a estrutura de um carro e declara os seus métodos.
 * 
 * @file carro.h
 * @author ist1109247
*/
#ifndef CARRO_H
#define CARRO_H

#include "lista_registos.h"

#define TAMANHO_MATRICULA 9 // tamanho necessário para guardar matrícula
#define INDICE_PRIMEIRO_HIFEN 2 // índice do 1º hífen numa string com matrícula
#define INDICE_SEGUNDO_HIFEN 5 // indice do 2º hífen numa string com matrícula

struct Carro {
    char* matricula;
    int dentro_de_parque;
    Lista_Registos lista_registos;
};
typedef struct Carro Carro;

typedef void (*Operacao_Carro)(Carro*);


int matricula_valida(char* matricula);

Carro* cria_carro(char* matricula);

void imprime_carro_tudo(Carro* carro);

void liberta_carro(Carro* carro);

#endif
