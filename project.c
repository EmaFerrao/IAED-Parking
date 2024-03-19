/* iaed24 - ist1109247 - project */
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "parque.h"

#define FALSE 0
#define TRUE 1
 

void ler_input(){
    char linha[BUFSIZ];
    do {
        fgets(linha, sizeof(linha), stdin);
        switch (linha[0]){
            case 'p':
                le_parque(linha);
        }
    } while (linha[0] != 'q');
}



int main(){
    ler_input();
    
    return 0;
}