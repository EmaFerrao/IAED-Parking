#ifndef CARRO_H
#define CARRO_H

#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "lista_registos.h"
#include "parque.h"

struct Carro {
    char* matricula;
    int dentro_de_parque;
    Lista_Registos lista_registos;
};
typedef struct Carro Carro;

typedef void (*Operacao_Carro)(Carro*);

Carro* cria_carro(char* matricula);
void libertar_carro(Carro* carro);

#endif
