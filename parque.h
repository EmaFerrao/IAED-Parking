#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct {
    char *nome;
    int capacidade;
    int lugares_disponiveis;
    float valor_15;
    float valor_15_apos_1hora;
    float valor_max_diario;
//    fatura* faturacao;
} Parque;

typedef struct parque_no{
    Parque* parque;
    struct parque_no* next;
} Parque_No;

int nao_tem_argumentos(char* linha);
int caracterbranco(char caracter);
void copia_char_incrementa_posicao(char* buffer, char* linha, int* posicao, int* i);
char* le_nome_parque(char* linha, int* posicao);
int verifica_argumentos_parque(int capacidade, float valor_15, float valor_15_apos_1hora, float valor_max_diario);
Parque* procura_parque(char* nome, Parque_No** pp_primeiro_parque);
void lista_parques(Parque_No** pp_primeiro_parque);
void cria_parque(char* nome, int capacidade, float valor_15, float valor_15_apos_1hora, 
    float valor_max_diario, Parque_No** pp_primeiro_parque, Parque_No** pp_ultimo_parque, int* numero_parques); 
void le_parque(char* linha, Parque_No** pp_primeiro_parque, Parque_No** pp_ultimo_parque, int* numero_parques);
