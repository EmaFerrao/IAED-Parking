#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct {
    char *nome;
    int capacidade;
    float valor_15;
    float valor_15_apos_1hora;
    float valor_max_diario;
//    fatura* faturacao;
} Parque;

typedef struct parque_no{
    Parque* parque;
    struct parque_no* next;
} Parque_No;

char* le_nome_parque(char* linha);
Parque* procura_parque(char* nome);
void le_parque(char* linha);
