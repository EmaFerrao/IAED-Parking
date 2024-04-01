#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "registo.h"
#include "carro.h"
#include "parque.h"

Registo* cria_registo(Parque* parque, Carro* carro, Data* entrada) {
    Registo* registo = (Registo*) malloc(sizeof(Registo));
    registo->parque = parque;
    registo->carro = carro;
    registo->entrada = entrada;
    registo->saida = NULL;
    registo->custo = 0;
    return registo;
}

void guarda_saida_no_registo(Registo* registo, Data* data_saida) {
    registo->saida = data_saida;
}

void guarda_custo_no_registo(Registo* registo, float custo) {
    registo->custo = custo;
}

void imprime_saida(Registo* registo) {
    printf("%s %02d-%02d-%02d %02d:%02d %02d-%02d-%02d %02d:%02d %.2f\n",
    registo->carro->matricula, registo->entrada->dia, registo->entrada->mes,
    registo->entrada->ano, registo->entrada->hora, registo->entrada->minutos, 
    registo->saida->dia, registo->saida->mes, registo->saida->ano,
    registo->saida->hora, registo->saida->minutos, registo->custo);
}

void imprime_entrada_saida(Registo* registo) {
    if (registo->saida == NULL) {
        printf("%s %02d-%02d-%02d %02d:%02d\n",
        registo->parque->nome, registo->entrada->dia, registo->entrada->mes,
        registo->entrada->ano, registo->entrada->hora, registo->entrada->minutos);
    } else {
        printf("%s %02d-%02d-%02d %02d:%02d %02d-%02d-%02d %02d:%02d\n",
        registo->parque->nome, registo->entrada->dia, registo->entrada->mes,
        registo->entrada->ano, registo->entrada->hora, registo->entrada->minutos, 
        registo->saida->dia, registo->saida->mes, registo->saida->ano,
        registo->saida->hora, registo->saida->minutos);
    }
}

void imprime_registo(Registo* registo) {
    if (registo->saida == NULL) {
        printf("%s %s %02d-%02d-%02d %02d:%02d\n",
        registo->parque->nome, registo->carro->matricula, registo->entrada->dia, registo->entrada->mes,
        registo->entrada->ano, registo->entrada->hora, registo->entrada->minutos);
    } else {
        printf("%s %s %02d-%02d-%02d %02d:%02d %02d-%02d-%02d %02d:%02d\n",
        registo->parque->nome, registo->carro->matricula, registo->entrada->dia, registo->entrada->mes,
        registo->entrada->ano, registo->entrada->hora, registo->entrada->minutos, 
        registo->saida->dia, registo->saida->mes, registo->saida->ano,
        registo->saida->hora, registo->saida->minutos);
    }
}

void liberta_registo(Registo* registo) {
// parque e carro nao pertencem a registo, logo nao sao libertados com registo
    free(registo->entrada);
    if (registo->saida!=NULL) free(registo->saida);
    free(registo);
}