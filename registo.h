#ifndef REGISTO_H
#define REGISTO_H

#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>

typedef struct {
    char* nome_parque;
    char* matricula;
    int entrada;
    int saida;
    int custo;
} Registo;

typedef struct registo_node {
    Registo* registo;
    struct registo_node* next;
} Registo_Node;

struct registos_lista{
    Registo_Node* head;
    Registo_Node* tail;
};
typedef struct registos_lista* Lista_Registos;

typedef void (*Operacao_Registo)(Registo*);

void libertar_registo(Registo* registo);

//Lista de Registos
Lista_Registos cria_lista_registos();
void itera_lista_registos(Lista_Registos lista_registos, Operacao_Registo operacao);
Registo* procura_registo(Lista_Registos lista_registos, char* matricula);
void append_lista_registos(Lista_Registos lista_registos, Registo* registo);
void libertar_lista_registos(Lista_Registos lista_registos, int libertar_registos);

#endif
