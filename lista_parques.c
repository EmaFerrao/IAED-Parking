/**
 * Define os métodos de uma lista de parques.
 * 
 * @file lista_parques.c
 * @author ist1109247
*/
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "lista_parques.h"

/**
 * @brief Cria e devolve uma nova lista de parques, que tem 
 * de ser libertada quando deixar de ser utilizada.
 */
Lista_Parques cria_lista_parques() {
    Lista_Parques lista_parques = (Lista_Parques) 
                                   malloc(sizeof(struct parques_lista));
    lista_parques->head = NULL;
    lista_parques->tail = NULL;
    lista_parques->numero_parques = 0;
    return lista_parques;
}

/**
 * @brief Insere o parque recebido no fim da lista de parques recebida.
 */
void insere_parque_no_fim(Lista_Parques lista_parques, Parque* parque) {
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

/**
 * @brief Percorre a lista de parques recebida, 
 * executando uma operação em cada parque.
 * 
 * @param lista_parques 
 * @param operacao função que recebe um parque e não devolve nada.
 */
void itera_lista_parques(Lista_Parques lista_parques, Operacao_Parque operacao) {
    Parque_Node* aux = lista_parques->head;
    while (aux != NULL) {
        operacao(aux->parque);
        aux = aux -> next;
    }
}


/**
 * @brief Recebe um nome e devolve o parque com 
 * esse nome na lista de parques recebida. Se a 
 * lista não tiver um parque com esse nome, devolve NULL.
 */
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

/**
 * @brief Percorre a lista de parques e, para cada parque, 
 * imprime o seu nome, a capacidade e o número de lugares disponíveis. 
 */
void imprime_lista_parques(Lista_Parques lista_parques) {
    itera_lista_parques(lista_parques, imprime_parque_capacidade_lugares);
}

/**
 * @brief Cria um vetor de strings com os nomes 
 * dos parques da lista de parques recebida.
 */
void cria_vetor_nomes_parques(Lista_Parques lista_parques, 
                              char** nomes_parques, int numero_parques) {
    Parque_Node* aux = lista_parques->head;

    for (int i = 0; i < numero_parques; i++) {
        nomes_parques[i] = aux->parque->nome;
        aux = aux -> next;
    }
}

/**
 * @brief Ordena um vetor de strings por ordem ASCII.
 */
void ordena_vetor_por_nome(char** vetor, int tamanho) {
    int i, j;
    char* temporario;

    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - i - 1; j++) {
            if (strcmp(vetor[j], vetor[j + 1]) > 0) {
                temporario = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temporario;
            }
        }
    }
}

/**
 * @brief Percorre um vetor de strings e imprime os seus elementos.
 */
void imprime_vetor(char** vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%s\n", vetor[i]);
    }
}

/**
 * @brief Imprime, por ordem ASCII, os nomes 
 * dos parques da lista de parques recebida.
 */
void imprime_lista_parques_por_nome(Lista_Parques lista_parques) {
    int numero_parques = lista_parques->numero_parques;
    char* nomes_parques[numero_parques];
    cria_vetor_nomes_parques(lista_parques, nomes_parques, numero_parques);
    ordena_vetor_por_nome(nomes_parques, numero_parques);
    imprime_vetor(nomes_parques, numero_parques);
}

/**
 * @brief Apaga o parque recebido da lista de parques recebida. 
 * Apaga os registos do parque, nas suas listas e nas 
 * listas de registos dos carros. 
 */
void remove_parque(Lista_Parques lista_parques, Parque* parque) {
    Parque_Node* aux = lista_parques->head;
    Parque_Node* anterior = NULL;
    Parque_Node* apagar = NULL;

    while (aux != NULL) {
        if (aux->parque == parque) {
            apagar = aux;
            if (anterior) {
                anterior->next = aux->next;
            } else {
                lista_parques->head = aux->next;
            }

            if (aux == lista_parques->tail) {
                lista_parques->tail = anterior;
            }
            liberta_parque(parque);
            free(apagar);
            lista_parques->numero_parques -= 1;
            return;
        } else {
            anterior = aux;
            aux = aux->next;
        }
    }
}

/**
 * @brief Liberta a lista de parques recebida e os 
 * seus nós, podendo ou não libertar os parques,
 * (depende do parâmetro libertar_parques).
 */
void liberta_lista_parques(Lista_Parques lista_parques, int libertar_parques) {
    Parque_Node* aux = lista_parques->head;
    Parque_Node* next;
    while (aux != NULL) {
        if (libertar_parques) {
            liberta_parque(aux->parque);
        }
        next = aux->next;
        free(aux);
        aux = next;
    }
    free(lista_parques);
}