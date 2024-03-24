#ifndef PARQUE_H
#define PARQUE_H

#define MAX_NOME_PARQUE 50

struct Parque {
    char *nome;
    int capacidade;
    int lugares_disponiveis;
    float valor_15;
    float valor_15_apos_1hora;
    float valor_max_diario;
//    fatura* faturacao;
};
typedef struct Parque Parque;

typedef void (*Operacao_Parque)(Parque*);

int verifica_argumentos_parque(int capacidade, float valor_15, float valor_15_apos_1hora, float valor_max_diario);
Parque* cria_parque(char* nome, int capacidade, float valor_15, float valor_15_apos_1hora, float valor_max_diario); 
void imprime_parque(Parque* parque);
void libertar_parque(Parque* parque);

#endif