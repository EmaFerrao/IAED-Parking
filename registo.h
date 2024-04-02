/**
 * Define a estrutura de um registo e declara os seus métodos.
 * 
 * @file registo.h
 * @author ist1109248
*/
#ifndef REGISTO_H
#define REGISTO_H
#include "data.h"

typedef struct Parque Parque;
typedef struct Carro Carro;

typedef struct {
    Parque* parque;
    Carro* carro;
    Data* entrada;
    Data* saida;
    float custo;
} Registo;

typedef void (*Operacao_Registo)(Registo*);


Registo* cria_registo(Parque* parque, Carro* carro, Data* entrada);

void imprime_saida(Registo* registo);

void imprime_entrada_saida(Registo* registo);

void imprime_registo_tudo(Registo* registo);

void liberta_registo(Registo* registo);

#endif
