#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "lista_carros.h"

Lista_Carros cria_lista_carros() {
    Lista_Carros lista_carros = (Lista_Carros) malloc(sizeof(struct carros_lista));
    lista_carros->head = NULL;
    lista_carros->tail = NULL;
    return lista_carros;
}

void itera_lista_carros(Lista_Carros lista_carros, Operacao_Carro operacao) {
    Carro_Node* aux = lista_carros->head;
    while (aux != NULL) {
        operacao(aux->carro);
        aux = aux -> next;
    }
}

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

void append_lista_carros(Lista_Carros lista_carros, Carro* carro) {
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

void libertar_lista_carros(Lista_Carros lista_carros, int libertar_carros) {
    Carro_Node* aux = lista_carros->head;
    Carro_Node* next;
    while (aux != NULL) {
        if (libertar_carros) {
            libertar_carro(aux->carro);
        }
        next = aux->next;
        free(aux);
        aux = next;
    }
    free(lista_carros);
}