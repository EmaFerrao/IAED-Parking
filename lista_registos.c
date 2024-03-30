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

void insere_lista_registos_por_nome(Lista_Registos lista_registos, Registo* registo) {
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
    float faturacao_do_dia = 0;
    Data* data;
    if (aux != NULL) {
        data = aux->registo->saida;
    }
    while (aux != NULL) {
        if (!mesmo_dia(aux->registo->saida, data)) {
            printf("%02d-%02d-%02d %.2f\n", data->dia, data->mes, data->ano, faturacao_do_dia);
            data = aux->registo->saida;
            faturacao_do_dia = 0;
        }
        faturacao_do_dia += aux->registo->custo;
        if (aux->next == NULL) {
            printf("%02d-%02d-%02d %.2f\n", data->dia, data->mes, data->ano, faturacao_do_dia);
        }
        aux = aux -> next;
    }
}

void imprime_faturacao_num_dia(Registo_Node* registo_node, Data* data) {
    while (registo_node != NULL && mesmo_dia(registo_node->registo->saida, data)) {
        printf("%s %02d:%02d %.2f\n", registo_node->registo->carro->matricula, 
        registo_node->registo->saida->hora, registo_node->registo->saida->minutos,
        registo_node->registo->custo);

        registo_node = registo_node->next;
    }
}

void apaga_registos_parque(Lista_Registos lista_registos, Parque* parque) {
    Registo_Node* aux = lista_registos->head;
    HashTable_Carros carros_visitados = criar_hashtable_carros(500);
    Carro* carro;
    while (aux != NULL) {
        if (aux->registo != NULL) {
            carro = aux->registo->carro;
            if (procurar_hashtable_carros(carros_visitados, carro->matricula) == NULL) {
                filtra_registos_carro(carro->lista_registos, parque);
                altera_carro_dentro_de_parque(carro, FALSE);
                inserir_hashtable_carros(carros_visitados, carro);
            }
        }
        aux = aux -> next;
    }
    libertar_hashtable_carros(carros_visitados, FALSE /*não quero libertar os carros*/);
    libertar_lista_registos(lista_registos, TRUE);
}

void filtra_registos_carro(Lista_Registos lista_registos, Parque* parque) {
    Registo_Node* current = lista_registos->head;
    Registo_Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->registo->parque->nome, parque->nome) == 0) {
            Registo_Node* toDelete = current;
            if (prev) {
                prev->next = current->next;
            } else {
                lista_registos->head = current->next;
            }
            if (current == lista_registos->tail) {
                lista_registos->tail = prev;
            }
            current = current->next;
            free(toDelete);
        } else {
            prev = current;
            current = current->next;
        }
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