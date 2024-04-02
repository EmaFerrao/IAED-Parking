/**
 * Define os métodos de um registo.
 * 
 * @file registo.c
 * @author ist1109248
*/
#include <stdio.h> 
#include <stdlib.h>
#include "registo.h"
#include "carro.h"
#include "parque.h"

/**
 * @brief Cria e devolve um novo registo, que tem 
 * de ser libertado quando deixar de ser utilizado.
 */
Registo* cria_registo(Parque* parque, Carro* carro, Data* entrada) {
    Registo* registo = (Registo*) malloc(sizeof(Registo));
    registo->parque = parque;
    registo->carro = carro;
    registo->entrada = entrada;
    registo->saida = NULL;
    registo->custo = 0;
    return registo;
}

/**
 * @brief Imprime o registo recebido, com a informação pedida no comando "s".
 * (ex: AA-00-AA 01-01-2024 08:00 01-01-2024 17:00 5.00)
 */
void imprime_saida(Registo* registo) {
    printf("%s %02d-%02d-%02d %02d:%02d %02d-%02d-%02d %02d:%02d %.2f\n",
    registo->carro->matricula, registo->entrada->dia, registo->entrada->mes,
    registo->entrada->ano, registo->entrada->hora, registo->entrada->minutos, 
    registo->saida->dia, registo->saida->mes, registo->saida->ano,
    registo->saida->hora, registo->saida->minutos, registo->custo);
}

/**
 * @brief Imprime o registo recebido, com a informação pedida no comando "v". 
 * Se o registo tiver data de saída, imprime essa data, senão, não a imprime.
 * (ex: parque 01-01-2024 08:00 01-01-2024 17:00)
 */
void imprime_entrada_saida(Registo* registo) {
    if (registo->saida == NULL) {
        printf("%s %02d-%02d-%02d %02d:%02d\n",
        registo->parque->nome, registo->entrada->dia, 
        registo->entrada->mes, registo->entrada->ano, 
        registo->entrada->hora, registo->entrada->minutos);
    } else {
        printf("%s %02d-%02d-%02d %02d:%02d %02d-%02d-%02d %02d:%02d\n",
        registo->parque->nome, registo->entrada->dia, registo->entrada->mes,
        registo->entrada->ano, registo->entrada->hora, registo->entrada->minutos, 
        registo->saida->dia, registo->saida->mes, registo->saida->ano,
        registo->saida->hora, registo->saida->minutos);
    }
}

/**
 * @brief Imprime toda a informação do registo recebido. Se o registo 
 * tiver data de saída, imprime essa data, senão, não a imprime.
 * (ex: parque AA-00-AA 01-01-2024 08:00 01-01-2024 17:00 5.00)
 */
void imprime_registo_tudo(Registo* registo) {
    if (registo->saida == NULL) {
        printf("%s %s %02d-%02d-%02d %02d:%02d %.2f\n",
        registo->parque->nome, registo->carro->matricula, registo->entrada->dia, 
        registo->entrada->mes, registo->entrada->ano, registo->entrada->hora, 
        registo->entrada->minutos, registo->custo);
    } else {
        printf("%s %s %02d-%02d-%02d %02d:%02d %02d-%02d-%02d %02d:%02d %.2f\n",
        registo->parque->nome, registo->carro->matricula, registo->entrada->dia,
        registo->entrada->mes, registo->entrada->ano, registo->entrada->hora, 
        registo->entrada->minutos, registo->saida->dia, registo->saida->mes, 
        registo->saida->ano, registo->saida->hora, registo->saida->minutos, 
        registo->custo);
    }
}

/**
 * @brief Liberta o registo e as datas lá guardadas.
 */
void liberta_registo(Registo* registo) {
// parque e carro não pertencem a registo, logo não são libertados com registo
    free(registo->entrada);
    if (registo->saida != NULL) {
        free(registo->saida);
    } 
    free(registo);
}