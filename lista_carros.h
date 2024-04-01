#ifndef LISTA_CARROS_H
#define LISTA_CARROS_H

#include "carro.h"

typedef struct carro_node{
    Carro* carro;
    struct carro_node* next;
} Carro_Node;

struct carros_lista{
    Carro_Node* head;
    Carro_Node* tail;
};
typedef struct carros_lista* Lista_Carros;

Lista_Carros cria_lista_carros();
void insere_carro_no_fim(Lista_Carros lista_carros, Carro* carro);
void itera_lista_carros(Lista_Carros lista_carros, Operacao_Carro operacao);
Carro* procura_carro(Lista_Carros lista_carros, char* matricula);
void liberta_lista_carros(Lista_Carros lista_carros, int libertar_carros);

#endif
