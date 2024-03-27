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
    int custo;
} Registo;

typedef void (*Operacao_Registo)(Registo*);

Registo* criar_registo(Parque* parque, Carro* carro, Data* entrada);
void libertar_registo(Registo* registo);

#endif
