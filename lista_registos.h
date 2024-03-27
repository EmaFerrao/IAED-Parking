#ifndef LISTA_REGISTOS_H
#define LISTA_REGISTOS_H

#include "registo.h"

typedef struct registo_node {
    Registo* registo;
    struct registo_node* next;
} Registo_Node;

struct registos_lista{
    Registo_Node* head;
    Registo_Node* tail;
};
typedef struct registos_lista* Lista_Registos;

//Lista de Registos
Lista_Registos cria_lista_registos();
void itera_lista_registos(Lista_Registos lista_registos, Operacao_Registo operacao);
Registo* procura_registo_por_parque(Lista_Registos lista_registos, Parque* parque);
void append_lista_registos(Lista_Registos lista_registos, Registo* registo);
void libertar_lista_registos(Lista_Registos lista_registos, int libertar_registos);

#endif
