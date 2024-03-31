/**
 * Todas as funcoes relacionadas com parques.
 * @file parque.c
 * @author ist1109248
*/
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "parque.h"
#include "hashtable_carros.h"
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
    parque -> lista_entradas = cria_lista_registos();
    parque -> lista_saidas = cria_lista_registos();

    return parque;
}

void imprime_parque_capacidade_lugares(Parque* parque) {
    printf("%s %d %d\n", parque->nome, parque->capacidade, parque->lugares_disponiveis);
}

void imprime_parque_tudo(Parque* parque) {
    printf("%s %d %d\n", parque->nome, parque->capacidade, parque->lugares_disponiveis);
    printf("ENTRADAS:\n");
    itera_lista_registos(parque->lista_entradas, imprime_registo);
    printf("\n");
}

void apaga_registos_carros_do_parque(Parque* parque) {
    Registo_Node* aux = parque->lista_entradas->head;
    HashTable_Carros carros_visitados = criar_hashtable_carros(500);
    Carro* carro;
    while (aux != NULL) {
        if (aux->registo != NULL) {
            carro = aux->registo->carro;
            if (procurar_hashtable_carros(carros_visitados, carro->matricula) == NULL) {
                if (aux->registo == procura_registo_por_parque(carro->lista_registos, parque)) {
                    carro->dentro_de_parque = FALSE;
                }
                filtra_registos_carro(carro->lista_registos, parque);
                inserir_hashtable_carros(carros_visitados, carro);
            }
        }
        aux = aux -> next;
    }
    libertar_hashtable_carros(carros_visitados, FALSE /*não quero libertar os carros*/);
}

void libertar_parque(Parque* parque) {
    apaga_registos_carros_do_parque(parque);
    libertar_lista_registos(parque->lista_saidas, FALSE);
    libertar_lista_registos(parque->lista_entradas, TRUE);
    free(parque->nome);
    free(parque);
}



