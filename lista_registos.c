#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "lista_registos.h"
#include "carro.h"
#include "parque.h"

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
            if (aux->registo->custo_centimos == 0) {
                return aux->registo;
            }
        }
        aux = aux -> next;
    }
    return NULL;
} 

Registo_Node* procura_registo_por_dia(Lista_Registos lista_registos, Data* data) {
    Registo_Node* aux = lista_registos->head;
    while (aux != NULL) {
        if (mesmo_dia(aux->registo->saida, data)) {
            return aux;
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
    Registo_Node* anterior = NULL;
    Registo_Node* registo_node = (Registo_Node*) malloc(sizeof(Registo_Node));
    registo_node -> registo = registo;
    registo_node -> next = NULL;

    if (lista_registos->head == NULL) {
        lista_registos->head = registo_node;
        lista_registos->tail = registo_node;
        return;
    }
    while (aux != NULL) {
        if (strcmp(aux->registo->parque->nome, registo->parque->nome) > 0) {
            if (anterior == NULL) {
                lista_registos->head = registo_node;
            } else {
                anterior->next = registo_node;
            }
            registo_node->next = aux;
            return;
        } else {
            if (anterior == NULL) {
                anterior = aux;
            } else {
                anterior = anterior -> next;
            }
            aux = aux -> next;
            
        }
    }
    anterior->next = registo_node;
}

void imprime_faturacao(Lista_Registos lista_registos) {
    Registo_Node* aux = lista_registos->head;
    int custo_centimos = 0;
    float custo_euros;
    Data* data;
    if (aux != NULL) {
        data = aux->registo->saida;
    }
    while (aux != NULL) {
        if (!mesmo_dia(aux->registo->saida, data)) {
            custo_euros = custo_centimos / (float)100;
            printf("%02d-%02d-%02d %.2f\n", data->dia, data->mes, data->ano, custo_euros);
            data = aux->registo->saida;
            custo_centimos = 0;
        }
        custo_centimos += aux->registo->custo_centimos;
        if (aux->next == NULL) {
            custo_euros = custo_centimos / (float)100;
            printf("%02d-%02d-%02d %.2f\n", data->dia, data->mes, data->ano, custo_euros);
        }
        aux = aux -> next;
    }
}

void imprime_faturacao_num_dia(Registo_Node* registo_node, Data* data) {
    float custo_euros;
    while (registo_node != NULL && mesmo_dia(registo_node->registo->saida, data)) {
        custo_euros = registo_node->registo->custo_centimos / 100;
        printf("%s %02d:%02d %.2f\n", registo_node->registo->carro->matricula, 
        registo_node->registo->saida->hora, registo_node->registo->saida->minutos,
        custo_euros);

        registo_node = registo_node->next;
    }
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