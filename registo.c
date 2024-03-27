#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "registo.h"

Registo* criar_registo(Parque* parque, Carro* carro, Data* entrada) {
    Registo* registo = (Registo*) malloc(sizeof(Registo));
    registo->parque = parque;
    registo->carro = carro;
    registo->entrada = entrada;
    registo->saida = NULL;
    registo->custo = 0;
    return registo;
}

void libertar_registo(Registo* registo) {
    // o parque e o carro não pertencem ao registo, logo não são libertados com o registo
    free(registo->entrada);
    if (registo->saida!=NULL) free(registo->saida);
    free(registo);
}