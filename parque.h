#ifndef PARQUE_H
#define PARQUE_H

#include "lista_registos.h"

struct Parque {
    char *nome;
    int capacidade;
    int lugares_disponiveis;
    float valor_15;
    float valor_15_apos_1hora;
    float valor_max_diario;
    Lista_Registos lista_saidas;
};
typedef struct Parque Parque;

typedef void (*Operacao_Parque)(Parque*);

int verifica_argumentos_parque(int capacidade, float valor_15, float valor_15_apos_1hora, float valor_max_diario);
Parque* cria_parque(char* nome, int capacidade, float valor_15, float valor_15_apos_1hora, float valor_max_diario); 
void imprime_parque(Parque* parque);
void imprime_parque_tudo(Parque* parque);
void libertar_parque(Parque* parque);

#endif