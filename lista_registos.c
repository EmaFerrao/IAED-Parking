#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "lista_registos.h"

Lista_Registos cria_lista_registos() {
    Lista_Registos lista_registos = (Lista_Registos) malloc(sizeof(Lista_Registos));
    lista_registos->head = NULL;
    lista_registos->tail = NULL;
    return lista_registos;
}

void itera_lista_registos(Lista_Registos lista_registos, Operacao_Registo operacao) {
    Registo_Node* aux = lista_registos->head;
    while (aux != NULL) {
        operacao(aux->registo);
        aux = aux -> next;
    }
}

/* Registo* procura_registo(Lista_Registos lista_registos, char* matricula) {
    Registo_Node* aux = lista_registos->head;
    while (aux != NULL) {
        if (strcmp(aux->registo->matricula, matricula) == 0){
            return aux->registo;
        }
        aux = aux -> next;
    }
    return NULL;
} */

void append_lista_registos(Lista_Registos lista_registos, Registo* registo) {
    Registo_Node* registo_node = (Registo_Node*) malloc(sizeof(Registo_Node));
    registo_node -> registo = registo;
    registo_node -> next = NULL;

    if (lista_registos->head == NULL) {
        lista_registos->head = registo_node;
    } else {
        lista_registos->tail->next = registo_node;
    }
    lista_registos->tail = registo_node;
}

void libertar_lista_registos(Lista_Registos lista_registos, int libertar_registos) {
    if (lista_registos == NULL) {
        return;
    }
    Registo_Node* aux = lista_registos->head;
    Registo_Node* next;
    while (aux != NULL) {
        if (libertar_registos) {
            libertar_registo(aux->registo);
        }
        next = aux->next;
        free(aux);
        aux = next;
    }
    free(lista_registos);
}