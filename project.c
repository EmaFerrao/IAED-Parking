/* iaed24 - ist1109247 - project */
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "bool.h"
#include "comandos.h"

/* numero maximo de carros (10000) / 10
Assim, cada elemento da hashtable tem no maximo 10 carros 
*/
#define TAMANHO_HASHTABLE 1000  

int main(){
    Lista_Parques lista_parques = cria_lista_parques();
    HashTable_Carros hashtable_carros = cria_hashtable_carros(TAMANHO_HASHTABLE);
    Data* data_sistema = cria_data(2000,1,1,0,0);
    
    recebe_input_identifica_comando(lista_parques, hashtable_carros, data_sistema);

    liberta_lista_parques(lista_parques, TRUE);
    liberta_hashtable_carros(hashtable_carros, TRUE);
    free(data_sistema);

    return 0;
}