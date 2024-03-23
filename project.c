/* iaed24 - ist1109247 - project */
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "parque.h"

#define FALSE 0
#define TRUE 1
#define BUFSIZE 8192
 

void ler_input(Parque_No** head_parques, Parque_No** tail_parques, int* numero_parques){
    char buffer[BUFSIZE];
    char* linha;
    do {
        fgets(buffer, sizeof(buffer), stdin);
        linha = (char*) malloc(sizeof(char)*(strlen(buffer)+1));
        strcpy(linha,buffer);
        switch (*linha){
            case 'p':
                le_parque(linha, head_parques, tail_parques, numero_parques);
        }
    } while (*linha != 'q');
    free(linha);
}



int main(){
    Parque_No* head_parques = NULL;
    Parque_No* tail_parques = NULL;
    int numero_parques = 0;
    ler_input(&head_parques, &tail_parques, &numero_parques);
    
    return 0;
}