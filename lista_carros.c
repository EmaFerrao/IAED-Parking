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
 * @brief Cria uma nova lista de carros, que tem 
 * de ser libertada quando deixar de ser utilizada.
 * 
 * @return lista de carros 
 */
Lista_Carros cria_lista_carros() {
    Lista_Carros lista_carros = (Lista_Carros) 
                                 malloc(sizeof(struct carros_lista));
    lista_carros->head = NULL;
    lista_carros->tail = NULL;
    return lista_carros;
}

/**
 * @brief Insere um carro no fim da lista de carros.
 * 
 * @param lista_carros 
 * @param carro 
 */
void insere_carro_no_fim(Lista_Carros lista_carros, Carro* carro) {
    Carro_Node* carro_node = (Carro_Node*) malloc(sizeof(Carro_Node));
    carro_node -> carro = carro;
    carro_node -> next = NULL;

    if (lista_carros->head == NULL) {
        lista_carros->head = carro_node;
    } else {
        lista_carros->tail->next = carro_node;
    }
    lista_carros->tail = carro_node;
}

/**
 * @brief Percorre a lista de carros, executando uma operação em cada carro.
 * 
 * @param lista_carros 
 * @param operacao função que recebe um carro e não devolve nada.
 */
void itera_lista_carros(Lista_Carros lista_carros, Operacao_Carro operacao) {
    Carro_Node* aux = lista_carros->head;
    while (aux != NULL) {
        operacao(aux->carro);
        aux = aux -> next;
    }
}

/**
 * @brief Recebendo uma matrícula, devolve o carro correspondente. 
 * Se não houver um carro com essa matrícula, devolve NULL.
 * 
 * @param lista_carros 
 * @param matricula 
 * @return carro 
 */
Carro* procura_carro(Lista_Carros lista_carros, char* matricula) {
    Carro_Node* aux = lista_carros->head;
    while (aux != NULL) {
        if (strcmp(aux->carro->matricula, matricula) == 0){
            return aux->carro;
        }
        aux = aux -> next;
    }
    return NULL;
}

/**
 * @brief Liberta a memória da lista, podendo ou não libertar os carros.
 * 
 * @param lista_carros 
 * @param libertar_carros TRUE ou FALSE
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
