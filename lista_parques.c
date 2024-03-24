#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "lista_parques.h"

Lista_Parques cria_Lista_Parques() {
    Lista_Parques lista_parques = (Lista_Parques) malloc(sizeof(Lista_Parques));
    lista_parques->head = NULL;
    lista_parques->tail = NULL;
    lista_parques->numero_parques = 0;
    return lista_parques;
}

void itera_Lista_Parques(Lista_Parques lista_parques, Operacao_Parque operacao) {
    Parque_Node* aux = lista_parques->head;
    while (aux != NULL) {
        operacao(aux->parque);
        aux = aux -> next;
    }
}

Parque* procura_parque(Lista_Parques lista_parques, char* nome) {
    Parque_Node* aux = lista_parques->head;
    while (aux != NULL) {
        if (strcmp(aux->parque->nome, nome) == 0){
            return aux->parque;
        }
        aux = aux -> next;
    }
    return NULL;
}

void imprime_lista_parques(Lista_Parques lista_parques) {
    itera_Lista_Parques(lista_parques, imprime_parque);
}

void append_Lista_Parques(Lista_Parques lista_parques, Parque* parque) {
    Parque_Node* parque_node = (Parque_Node*) malloc(sizeof(Parque_Node));
    parque_node -> parque = parque;
    parque_node -> next = NULL;

    if (lista_parques->head == NULL) {
        lista_parques->head = parque_node;
    } else {
        lista_parques->tail->next = parque_node;
    }
    lista_parques->tail = parque_node;

    lista_parques->numero_parques += 1;
}

void libertar_lista_parques(Lista_Parques lista_parques, int libertar_parques) {
    Parque_Node* aux = lista_parques->head;
    Parque_Node* next;
    while (aux != NULL) {
        if (libertar_parques) {
            libertar_parque(aux->parque);
        }
        next = aux->next;
        free(aux);
        aux = next;
    }
    free(lista_parques);
}