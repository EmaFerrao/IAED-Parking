#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "registo.h"

#define FALSE 0
#define TRUE 1
#define TAMANHO_HASHTABLE 1000

typedef struct {
    char* matricula;
    Registo_Node* historico;
} Carro;

typedef struct carro_node{
    Carro* carro;
    struct carro_node* next;
} Carro_Node;

struct carros_lista{
    Carro_Node* head;
    Carro_Node* tail;
};
typedef struct carros_lista* Lista_Carros;

typedef void (*Operacao_Carro)(Carro*);

/* typedef struct {
    char* chave;
    Carro_Node* carro_node;
} HashNode_Carro;

struct tablehash {
    int tamanho;
    HashNode_Carro* hash_chaves[tamanho];
}; 
typedef struct tablehash* HashTable; */


long int cria_data(int dia, int mes, int ano, int hora, int minutos);
void registar_entrada(char* linha);
void ler_entrada(char* linha, char* matricula, char* nome_parque, long int* data);