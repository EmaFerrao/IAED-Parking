#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "estadia.h"

#define FALSE 0
#define TRUE 1

typedef struct {
    char* matricula;
    Estadia_No* historico;
} Carro;

typedef struct carro_no{
    Carro* carro;
    struct carro_no* next;
} Carro_No;

typedef struct {
    int chave;
    Carro_No* lista;
} HashCarros;

void registar_entrada(char* linha);
void ler_entrada(char* linha, char* matricula, char* nome_parque, int* data);