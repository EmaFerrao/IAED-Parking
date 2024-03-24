#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct {
    char* nome_parque;
    char* matricula;
    int entrada;
    int saida;
    int custo;
} Registo;

typedef struct registo_node {
    Registo* registo;
    struct registo_node* next;
} Registo_Node;
