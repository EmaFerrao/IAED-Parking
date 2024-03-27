#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "lista_registos.h"
#include "carro.h"

Lista_Registos cria_lista_registos() {
    Lista_Registos lista_registos = (Lista_Registos) malloc(sizeof(struct registos_lista));
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

Registo* procura_registo_por_parque(Lista_Registos lista_registos, Parque* parque) {
    Registo_Node* aux = lista_registos->head;
    while (aux != NULL) {
        if (aux->registo->parque == parque) {
            if (aux->registo->custo == 0) {
                return aux->registo;
            }
        }
        aux = aux -> next;
    }
    return NULL;
} 

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

void insere_lista_registos_alfabeto(Lista_Registos lista_registos, Registo* registo) {
    Registo_Node* aux = lista_registos->head;
    Registo_Node* anterior = aux;
    Registo_Node* registo_node = (Registo_Node*) malloc(sizeof(Registo_Node));
    registo_node -> registo = registo;
    registo_node -> next = NULL;

    if (lista_registos->head == NULL) {
        lista_registos->head = registo_node;
        lista_registos->tail = registo_node;
        return;
    }
    while (aux != NULL) {
        if (strcmp(aux->registo->carro->matricula, registo->carro->matricula) > 0) {
            anterior->next = registo_node;
            registo_node->next = aux;
            return;
        } else {
            aux = aux -> next;
            anterior = anterior -> next;
        }
    }
    anterior->next = registo_node;
    return;
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