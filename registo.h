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

Registo* criar_registo(Parque* parque, Carro* carro, Data* entrada);
void guarda_saida_no_registo(Registo* registo, Data* data_saida);
void guarda_custo_no_registo(Registo* registo, float custo);
void imprime_registo(Registo* registo);
void libertar_registo(Registo* registo);

#endif
