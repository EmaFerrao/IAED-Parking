/* iaed24 - ist1109247 - project */
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "carro.h"

#define FALSE 0
#define TRUE 1
#define BUFSIZE 8192
#define TAMANHO_HASHTABLE 1000
 

void ler_input(Lista_Parques lista_parques, HashTable_Carros hastable_carros){
    char linha[BUFSIZE];
    do {
        fgets(linha, sizeof(linha), stdin);
        switch (linha[0]){
            case 'p':
                le_parque(linha, lista_parques);
                break;
            case 'e':
                comando_e(linha, lista_parques, hastable_carros);
        }
    } while (linha[0] != 'q');
}


int main(){
    Lista_Parques lista_parques = cria_Lista_Parques();
    HashTable_Carros hashtable_carros = criar_hashtable_carros(TAMANHO_HASHTABLE);
    ler_input(lista_parques, hashtable_carros);
    libertar_lista_parques(lista_parques, TRUE);
    
    return 0;
}