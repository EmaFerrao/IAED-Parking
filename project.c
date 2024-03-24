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
 

void ler_input(Lista_Parques* lista_parques){
    char linha[BUFSIZE];
    do {
        fgets(linha, sizeof(linha), stdin);
        switch (linha[0]){
            case 'p':
                le_parque(linha, lista_parques);
                break;
            case 'e':
                registar_entrada(linha);
        }
    } while (linha[0] != 'q');
}
//ola



int main(){
    Lista_Parques* lista_parques;
    lista_parques = cria_Lista_Parques();
    ler_input(lista_parques);
    libertar_lista_parques(lista_parques);
    
    return 0;
}