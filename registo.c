#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "registo.h"

void libertar_registo(Registo* registo) {
    // o parque e o carro não pertencem ao registo, logo não são libertados com o registo
    free(registo->data_entrada);
    free(registo->hora_entrada);
    free(registo->data_saida);
    free(registo->hora_saida);
    free(registo);
}