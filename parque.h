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

typedef void (*Operacao_Parque)(Parque*);

int nao_tem_argumentos(char* linha);
int caracterbranco(char caracter);
void copia_char_incrementa_posicao(char* buffer, char* linha, int* posicao, int* i);
char* le_nome_parque(char* linha, int* posicao);
int verifica_argumentos_parque(int capacidade, float valor_15, float valor_15_apos_1hora, float valor_max_diario);
void cria_parque(char* nome, int capacidade, float valor_15, float valor_15_apos_1hora, 
    float valor_max_diario, Lista_Parques lista_parques); 
void imprime_parque(Parque* parque);
void libertar_parque(Parque* parque);
void le_parque(char* linha, Lista_Parques lista_parques);

//Lista de Parques
Lista_Parques cria_Lista_Parques();
void itera_Lista_Parques(Lista_Parques lista_parques, Operacao_Parque operacao);
Parque* procura_parque(char* nome, Lista_Parques lista_parques);
void imprime_lista_parques(Lista_Parques lista_parques);
void append_Lista_Parques(Lista_Parques lista_parques, Parque* parque);
void libertar_lista_parques(Lista_Parques lista_parques, int libertar_parques);
