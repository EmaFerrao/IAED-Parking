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
void insere_registo_no_fim(Lista_Registos lista_registos, Registo* registo);
void insere_registo_por_nome_parque(Lista_Registos lista_registos, Registo* registo);
void itera_lista_registos(Lista_Registos lista_registos, Operacao_Registo operacao);
Registo* procura_registo_sem_saida_no_parque(Lista_Registos lista_registos, Parque* parque);
Registo_Node* procura_primeiro_registo_node_do_dia(Lista_Registos lista_registos, Data* data);
void imprime_faturacao(Lista_Registos lista_registos);
void imprime_faturacao_num_dia(Registo_Node* registo, Data* data);
void filtra_registos_carro(Lista_Registos lista_registos, Parque* parque);
void libertar_lista_registos(Lista_Registos lista_registos, int libertar_registos);

#endif
