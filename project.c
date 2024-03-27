/* iaed24 - ist1109247 - project */
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "bool.h"
#include "comandos.h"

#define BUFSIZE 8192
#define CARROS_ESPERADOS 10000

int main(){
    char linha[BUFSIZE];
    Lista_Parques lista_parques = cria_Lista_Parques();
    HashTable_Carros hashtable_carros = criar_hashtable_carros(CARROS_ESPERADOS);
    Data* data_sistema = cria_data(2000,1,1,0,0);
    
    do {
        fgets(linha, sizeof(linha), stdin);
        switch (linha[0]){
            case 'p':
                comando_p(linha, lista_parques);
                break;
            case 'e':
                comando_e(linha, lista_parques, hashtable_carros, data_sistema);
                break;
            case 's':
                comando_s(linha, lista_parques, hashtable_carros, data_sistema);
                break;
            case 'v':
                comando_v(linha, hashtable_carros);
        }
    } while (linha[0] != 'q');

    libertar_lista_parques(lista_parques, TRUE);
    libertar_hashtable_carros(hashtable_carros, TRUE);
    free(data_sistema);
    return 0;
}