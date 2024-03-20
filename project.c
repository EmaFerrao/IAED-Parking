/* iaed24 - ist1109247 - project */
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "parque.h"

#define FALSE 0
#define TRUE 1
 

void ler_input(Parque_No* primeiro_parque, Parque_No* ultimo_parque, int* numero_parques){
    char linha[BUFSIZ];
    do {
        fgets(linha, sizeof(linha), stdin);
        switch (linha[0]){
            case 'p':
                le_parque(linha, primeiro_parque, ultimo_parque, numero_parques);
        }
    } while (linha[0] != 'q');
}



int main(){
    Parque_No* primeiro_parque = NULL;
    Parque_No* ultimo_parque = NULL;
    int* numero_parques = 0;
    ler_input(primeiro_parque, ultimo_parque, numero_parques);
    
    return 0;
}