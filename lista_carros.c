/**
 * Define os métodos de uma lista de carros.
 * 
 * @file lista_carros.c
 * @author ist1109247
*/
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "lista_carros.h"

/**
 * @brief Cria e devolve uma nova lista de carros, que tem 
 * de ser libertada quando deixar de ser utilizada.
 */
Lista_Carros cria_lista_carros() {
    Lista_Carros lista_carros = (Lista_Carros) 
                                 malloc(sizeof(struct carros_lista));
    lista_carros->head = NULL;
    lista_carros->tail = NULL;
    return lista_carros;
}

/**
 * @brief Insere o carro recebido no fim da lista de carros recebida.
 */
void insere_carro_no_fim(Lista_Carros lista_carros, Carro* carro) {
    Carro_Node* carro_node = (Carro_Node*) malloc(sizeof(Carro_Node));
    carro_node->carro = carro;
    carro_node->next = NULL;

    if (lista_carros->head == NULL) {
        lista_carros->head = carro_node;
    } else {
        lista_carros->tail->next = carro_node;
    }
    lista_carros->tail = carro_node;
}

/**
 * @brief Percorre a lista de carros recebida, 
 * executando uma operação em cada carro.
 * 
 * @param lista_carros 
 * @param operacao função que recebe um carro e não devolve nada.
 */
void itera_lista_carros(Lista_Carros lista_carros, Operacao_Carro operacao) {
    Carro_Node* aux = lista_carros->head;
    while (aux != NULL) {
        operacao(aux->carro);
        aux = aux->next;
    }
}

/**
 * @brief Recebe uma matrícula e devolve o carro com 
 * essa matrícula na lista de carros recebida. Se a 
 * lista não tiver um carro com essa matrícula, devolve NULL.
 */
Carro* procura_carro(Lista_Carros lista_carros, char* matricula) {
    Carro_Node* aux = lista_carros->head;
    while (aux != NULL) {
        if (strcmp(aux->carro->matricula, matricula) == 0){
            return aux->carro;
        }
        aux = aux->next;
    }
    return NULL;
}

/**
 * @brief Liberta a lista de carros recebida e os 
 * seus nós, podendo ou não libertar os carros 
 * (depende do parâmetro libertar_carros).
 */
void liberta_lista_carros(Lista_Carros lista_carros, int libertar_carros) {
    Carro_Node* aux = lista_carros->head;
    Carro_Node* next;
    while (aux != NULL) {
        if (libertar_carros) {
            liberta_carro(aux->carro);
        }
        next = aux->next;
        free(aux);
        aux = next;
    }
    free(lista_carros);
}
