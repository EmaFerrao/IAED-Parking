#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "registo.h"

#define FALSE 0
#define TRUE 1

typedef struct {
    char* matricula;
    Registo_Node* historico;
} Carro;

typedef struct carro_node{
    Carro* carro;
    struct carro_node* next;
} Carro_Node;

typedef struct {
    int chave;
    Carro_Node* lista;
} HashCarros;

long int cria_data(int dia, int mes, int ano, int hora, int minutos);
void registar_entrada(char* linha);
void ler_entrada(char* linha, char* matricula, char* nome_parque, long int* data);