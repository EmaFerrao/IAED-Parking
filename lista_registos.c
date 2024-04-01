#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "bool.h"
#include "lista_registos.h"
#include "parque.h"
#include "hashtable_carros.h"

Lista_Registos cria_lista_registos() {
    Lista_Registos lista_registos = (Lista_Registos) malloc(sizeof(struct registos_lista));
    lista_registos->head = NULL;
    lista_registos->tail = NULL;
    return lista_registos;
}

void insere_registo_no_fim(Lista_Registos lista_registos, Registo* registo) {
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

void insere_registo_por_nome_parque(Lista_Registos lista_registos, Registo* registo) {
    Registo_Node* aux = lista_registos->head, *anterior = NULL;
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

void itera_lista_registos(Lista_Registos lista_registos, Operacao_Registo operacao) {
    Registo_Node* aux = lista_registos->head;
    while (aux != NULL) {
        operacao(aux->registo);
        aux = aux -> next;
    }
}

Registo* procura_registo_sem_saida_no_parque(Lista_Registos lista_registos, Parque* parque) {
    Registo_Node* aux = lista_registos->head;
    while (aux != NULL) {
        if (aux->registo->parque == parque) {
            if (aux->registo->saida == NULL) {
                return aux->registo;
            }
        }
        aux = aux -> next;
    }
    return NULL;
} 

Registo_Node* procura_primeiro_registo_node_do_dia(Lista_Registos lista_registos, Data* data) {
    Registo_Node* aux = lista_registos->head;
    while (aux != NULL) {
        if (mesmo_dia(aux->registo->saida, data)) {
            return aux;
        }
        aux = aux -> next;
    }
    return NULL;
} 

void imprime_faturacao(Lista_Registos lista_registos) {
    Registo_Node* aux = lista_registos->head;
    float faturacao_do_dia = 0;

    while (aux != NULL) {
        faturacao_do_dia += aux->registo->custo;
        if (aux->next == NULL || 
            !mesmo_dia(aux->registo->saida, aux->next->registo->saida)) {
            printf("%02d-%02d-%02d %.2f\n", 
                aux->registo->saida->dia, 
                aux->registo->saida->mes, 
                aux->registo->saida->ano, 
                faturacao_do_dia);

            faturacao_do_dia = 0;
        }
        aux = aux -> next;
    }
}

void imprime_faturacao_num_dia(Registo_Node* registo_node, Data* data) {
    while (registo_node != NULL && 
        mesmo_dia(registo_node->registo->saida, data)) {
        printf("%s %02d:%02d %.2f\n", 
            registo_node->registo->carro->matricula, 
            registo_node->registo->saida->hora, 
            registo_node->registo->saida->minutos,
            registo_node->registo->custo);

        registo_node = registo_node->next;
    }
}

void filtra_registos_carro(Lista_Registos lista_registos, Parque* parque) {
    Registo_Node* aux = lista_registos->head;
    Registo_Node* anterior = NULL;
    Registo_Node* apagar;

    while (aux != NULL) {
        if (aux->registo->parque == parque) {
            apagar = aux;
            if (anterior) {
                anterior->next = aux->next;
            } else {
                lista_registos->head = aux->next;
            }
            
            if (aux == lista_registos->tail) {
                lista_registos->tail = anterior;
            }
            aux = aux->next;
            free(apagar);
        } else {
            anterior = aux;
            aux = aux->next;
        }
    }
}

void libertar_lista_registos(Lista_Registos lista_registos, int libertar_registos) {
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