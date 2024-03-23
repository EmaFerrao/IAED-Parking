#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "data_hora.h"
#include "carro.h"

#define FALSE 0
#define TRUE 1

typedef struct {
    char* nome_parque;
    char* matricula;
    int entrada;
    int saida;
    int custo;
} Estadia;

typedef struct estadia_no {
    Estadia* estadia;
    struct estadia_no* next;
} Estadia_No;

