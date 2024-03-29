#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "lista_parques.h"

Lista_Parques cria_lista_parques() {
    Lista_Parques lista_parques = (Lista_Parques) malloc(sizeof(struct parques_lista));
    lista_parques->head = NULL;
    lista_parques->tail = NULL;
    lista_parques->numero_parques = 0;
    return lista_parques;
}

void itera_lista_parques(Lista_Parques lista_parques, Operacao_Parque operacao) {
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
    itera_lista_parques(lista_parques, imprime_parque);
}

void cria_vetor_nomes_parques(Lista_Parques lista_parques, char** nomes_parques, int numero_parques) {
    Parque_Node* aux = lista_parques->head;

    for (int i = 0; i < numero_parques; i++) {
        nomes_parques[i] = aux->parque->nome;
        aux = aux -> next;
    }
}

void ordena_vetor_por_nome(char** vetor, int tamanho) {
    int i, j;
    char temporario[100];

    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - i - 1; j++) {
            if (strcmp(vetor[j], vetor[j + 1]) > 0) {
                strcpy(temporario, vetor[j]);
                strcpy(vetor[j], vetor[j + 1]);
                strcpy(vetor[j + 1], temporario);
            }
        }
    }
}

void imprime_vetor(char** vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%s\n", vetor[i]);
    }
}

void imprime_lista_parques_por_nome(Lista_Parques lista_parques) {
    int numero_parques = lista_parques->numero_parques;
    char* nomes_parques[numero_parques];
    cria_vetor_nomes_parques(lista_parques, nomes_parques, numero_parques);
    ordena_vetor_por_nome(nomes_parques, numero_parques);
    imprime_vetor(nomes_parques, numero_parques);
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

void remove_parque(Lista_Parques lista_parques, Parque* parque) {
    Parque_Node* parque_anterior = lista_parques->head;
    Parque_Node* parque_node = NULL;
    while (parque_anterior != NULL) {
        if (strcmp(parque_anterior->next->parque->nome, parque->nome) == 0){
            parque_node = parque_anterior->next;
            break;
        }
        parque_anterior = parque_anterior -> next;
    }
    apaga_registos_parque_em_carros(parque->lista_saidas, parque);
    parque_anterior->next = parque_node->next;
    free(parque->nome);
    free(parque);
    free(parque_node);
    lista_parques->numero_parques -= 1;
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