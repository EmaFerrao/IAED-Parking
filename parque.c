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
#include "data.h"
#include "bool.h"

#define MINUTOS_NUMA_HORA 60    // uma hora tem 60 minutos
#define MINUTOS_NUMA_FRACAO 15  // uma fracao sao 15 minutos
#define FRACOES_NUMA_HORA 4     // uma hora tem 4 x 15 minutos -> 4 fracoes

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

float calcula_custo(Registo* registo, Parque* parque) {
    int minutos, dias;
    float custo_dias = 0, custo = 0;

    minutos = diferenca_em_minutos(registo->entrada, registo->saida);
    dias = minutos / MINUTOS_NUM_DIA;
    custo_dias += dias * parque->valor_max_diario;
    minutos = minutos % MINUTOS_NUM_DIA;

    if (minutos <= MINUTOS_NUMA_HORA) {
        custo += (minutos / MINUTOS_NUMA_FRACAO) * parque->valor_15;
        if (minutos % MINUTOS_NUMA_FRACAO != 0) {
            custo += parque->valor_15;
        }
    } else {
        custo += FRACOES_NUMA_HORA * parque->valor_15;
        minutos -= MINUTOS_NUMA_HORA;
        custo += (minutos / MINUTOS_NUMA_FRACAO) * parque->valor_15_apos_1hora;
        if (minutos % MINUTOS_NUMA_FRACAO != 0) {
            custo += parque->valor_15_apos_1hora;
        }
    }
    if (custo > parque->valor_max_diario) {
        custo = parque->valor_max_diario;
    }
    
    return custo_dias + custo;
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
    HashTable_Carros carros_visitados = criar_hashtable_carros(TAMANHO_HASHTABLE_CARROS_VISITADOS); 
    Carro* carro;
    Registo* registo_sem_saida;
    while (aux != NULL) {
        if (aux->registo != NULL) {
            carro = aux->registo->carro;
            if (procurar_hashtable_carros(carros_visitados, carro->matricula) == NULL) {
                registo_sem_saida = procura_registo_sem_saida_no_parque(carro->lista_registos, parque);
                if (registo_sem_saida != NULL && registo_sem_saida->parque == parque) {
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



