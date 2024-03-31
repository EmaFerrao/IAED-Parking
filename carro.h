#ifndef CARRO_H
#define CARRO_H

#include "lista_registos.h"

struct Carro {
    char* matricula;
    int dentro_de_parque;
    Lista_Registos lista_registos;
};
typedef struct Carro Carro;

typedef void (*Operacao_Carro)(Carro*);

Carro* cria_carro(char* matricula);
void imprime_carro_tudo(Carro* carro);
void libertar_carro(Carro* carro);

#endif
