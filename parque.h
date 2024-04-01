#ifndef PARQUE_H
#define PARQUE_H

#include "lista_registos.h"

// numero maximo de carros (10000) / numero maximo de parques (20)
#define TAMANHO_HASHTABLE_CARROS_VISITADOS 500

struct Parque {
    char *nome;
    int capacidade;
    int lugares_disponiveis;
    float valor_15;
    float valor_15_apos_1hora;
    float valor_max_diario;
    Lista_Registos lista_saidas;
    Lista_Registos lista_entradas;
};
typedef struct Parque Parque;

typedef void (*Operacao_Parque)(Parque*);

Parque* cria_parque(char* nome, int capacidade, float valor_15, 
    float valor_15_apos_1hora, float valor_max_diario); 
float calcula_custo(Registo* registo, Parque* parque);
void imprime_parque_capacidade_lugares(Parque* parque);
void imprime_parque_tudo(Parque* parque);
void libertar_parque(Parque* parque);

#endif