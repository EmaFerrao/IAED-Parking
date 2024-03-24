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

Lista_Parques cria_Lista_Parques();
void itera_Lista_Parques(Lista_Parques lista_parques, Operacao_Parque operacao);
Parque* procura_parque(char* nome, Lista_Parques lista_parques);
void imprime_lista_parques(Lista_Parques lista_parques);
void append_Lista_Parques(Lista_Parques lista_parques, Parque* parque);
void libertar_lista_parques(Lista_Parques lista_parques, int libertar_parques);

#endif