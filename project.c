/* iaed24 - ist1109247 - project */
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "parque.h"
#include "carro.h"

#define FALSE 0
#define TRUE 1
#define BUFSIZE 8192
 

void ler_input(Parque_No** head_parques, Parque_No** tail_parques, int* numero_parques){
    char linha[BUFSIZE];
    do {
        fgets(linha, sizeof(linha), stdin);
        switch (linha[0]){
            case 'p':
                le_parque(linha, head_parques, tail_parques, numero_parques);
                break;
            case 'e':
                registar_entrada(linha);
        }
    } while (linha[0] != 'q');
}



int main(){
    Parque_No* head_parques = NULL;
    Parque_No* tail_parques = NULL;
    int numero_parques = 0;
    ler_input(&head_parques, &tail_parques, &numero_parques);
    libertar_lista_parques(&head_parques);
    
    return 0;
}