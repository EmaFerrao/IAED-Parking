/**
 * Declara a função que recebe o input e identifica o 
 * comando e as funções específicas de cada comando.
 * 
 * @file comandos.h
 * @author ist1109247
*/
#ifndef COMANDOS_H
#define COMANDOS_H

#include "lista_parques.h"
#include "hashtable_carros.h"

#define BUFSIZE 8192 // número usado para receber input de tamanho desconhecido


void recebe_input_identifica_comando(Lista_Parques lista_parques, 
                                     HashTable_Carros hashtable_carros, 
                                     Data* data_sistema);

void comando_p(char* linha, Lista_Parques lista_parques);

void comando_e(char* linha, Lista_Parques lista_parques, 
               HashTable_Carros hashtable_carros, Data* data_sistema);

void comando_s(char* linha, Lista_Parques lista_parques, 
               HashTable_Carros hashtable_carros, Data* data_sistema);

void comando_v(char* linha, HashTable_Carros hashtable_carros);

void comando_f(char* linha, Lista_Parques lista_parques, Data* data_sistema);

void comando_r(char* linha, Lista_Parques lista_parques);

void comando_t(Lista_Parques lista_parques, HashTable_Carros hashtable_carros);

#endif
