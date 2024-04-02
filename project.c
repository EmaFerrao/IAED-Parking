/**
 * Ficheiro principal do projeto.
 * 
 * @file project.c
 * @author ist1109248
*/
#include <stdlib.h>
#include "bool.h"
#include "comandos.h"

/* número máximo de carros (10000) / 10
Assim, cada elemento da hashtable tem no máximo 10 carros */
#define TAMANHO_HASHTABLE 1000  

/**
 * @brief Função principal do projeto. Inicializa as estruturas 
 * necessárias, processa o input até o programa ser terminado 
 * pelo utilizador e liberta as estruturas.
 */
int main(){
    Lista_Parques lista_parques = cria_lista_parques();
    HashTable_Carros hashtable_carros = cria_hashtable_carros(TAMANHO_HASHTABLE);
    Data* data_sistema = cria_data(2000,1,1,0,0);
    
    recebe_input_identifica_comando(lista_parques, hashtable_carros, 
                                    data_sistema);

    liberta_lista_parques(lista_parques, TRUE);
    liberta_hashtable_carros(hashtable_carros, TRUE);
    free(data_sistema);
    return 0;
}