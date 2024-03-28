/**
 * Todas as funcoes relacionadas com parques.
 * @file parque.c
 * @author ist1109248
*/
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "parque.h"
#include "bool.h"

int verifica_argumentos_parque(int capacidade, float valor_15, float valor_15_apos_1hora, float valor_max_diario) {
    if (capacidade <= 0) {
        printf("%d: invalid capacity.\n", capacidade);
        return FALSE;
    }

    if (valor_15 <= 0 || valor_15_apos_1hora <= 0 || valor_max_diario <= 0) {
        printf("invalid cost.\n");
        return FALSE;
    }

    if (!(valor_15 < valor_15_apos_1hora && valor_15_apos_1hora < valor_max_diario)) {
        printf("invalid cost.\n");
        return FALSE;
    }

    return TRUE;
}

Parque* cria_parque(char* nome, int capacidade, float valor_15, float valor_15_apos_1hora, float valor_max_diario) {
        Parque* parque;
        parque = (Parque*) malloc(sizeof(Parque));
        parque -> nome = strdup(nome);
        parque -> capacidade = capacidade;
        parque -> lugares_disponiveis = capacidade;
        parque -> valor_15 = valor_15;
        parque -> valor_15_apos_1hora = valor_15_apos_1hora;
        parque -> valor_max_diario = valor_max_diario;
        parque -> lista_saidas = cria_lista_registos();

        return parque;
}

void imprime_parque(Parque* parque) {
    printf("%s %d %d\n", parque->nome, parque->capacidade, parque->lugares_disponiveis);
}

void remove_parque(Parque* parque) {
    apaga_registos_parque_em_carros(parque->lista_saidas, parque);
    libertar_parque(parque);
}

void libertar_parque(Parque* parque) {
    free(parque->nome);
    libertar_lista_registos(parque->lista_saidas, FALSE);
    free(parque);
}



