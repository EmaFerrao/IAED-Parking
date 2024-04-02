/**
 * Declara a estrutura de uma hashtable de carros e os seus métodos.
 * 
 * @file hashtable_carros.c
 * @author ist1109247
*/
#ifndef HASHTABLE_CARROS_H
#define HASHTABLE_CARROS_H

#include "lista_carros.h"

struct tablehashcarro {
    Lista_Carros* array_de_listas;
    int tamanho;
}; 
typedef struct tablehashcarro* HashTable_Carros; 


unsigned int hash(char *texto, int tamanho);

HashTable_Carros cria_hashtable_carros(int tamanho);

void insere_carro_na_hashtable(HashTable_Carros hashtable, Carro* carro);

Carro* procura_carro_na_hashtable(HashTable_Carros hashtable, char* matricula);

void imprime_hashtable_carros(HashTable_Carros hashtable);

void liberta_hashtable_carros(HashTable_Carros hashtable, int libertar_carros);

#endif
