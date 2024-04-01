#ifndef LISTA_PARQUES_H
#define LISTA_PARQUES_H

#include "parque.h"

typedef struct parque_node {
    Parque* parque;
    struct parque_node* next;
} Parque_Node;

struct parques_lista {
    Parque_Node* head;
    Parque_Node* tail;
    int numero_parques;
};
typedef struct parques_lista* Lista_Parques;

Lista_Parques cria_lista_parques();
void insere_parque_no_fim(Lista_Parques lista_parques, Parque* parque);
void itera_lista_parques(Lista_Parques lista_parques, Operacao_Parque operacao);
Parque* procura_parque(Lista_Parques lista_parques, char* nome) ;
void imprime_lista_parques(Lista_Parques lista_parques);
void imprime_lista_parques_por_nome(Lista_Parques lista_parques);
void remove_parque(Lista_Parques lista_parques, Parque* parque);
void liberta_lista_parques(Lista_Parques lista_parques, int libertar_parques);

#endif