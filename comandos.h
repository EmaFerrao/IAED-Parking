#ifndef COMANDOS_H
#define COMANDOS_H

#include "lista_parques.h"
#include "hashtable_carros.h"

void comando_p(char* linha, Lista_Parques lista_parques);
void comando_e(char* linha, Lista_Parques lista_parques, HashTable_Carros hashtable_carros);

#endif