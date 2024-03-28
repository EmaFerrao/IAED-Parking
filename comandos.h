#ifndef COMANDOS_H
#define COMANDOS_H

#include "lista_parques.h"
#include "hashtable_carros.h"

void comando_p(char* linha, Lista_Parques lista_parques);
void comando_e(char* linha, Lista_Parques lista_parques, HashTable_Carros hashtable_carros, Data* data_sistema);
void comando_s(char* linha, Lista_Parques lista_parques, HashTable_Carros hashtable_carros, Data* data_sistema);
void comando_v(char* linha, HashTable_Carros hashtable_carros);
void comando_f(char* linha, Lista_Parques lista_parques);

#endif