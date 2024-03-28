#ifndef HASHTABLE_CARROS_H
#define HASHTABLE_CARROS_H

#include "lista_carros.h"

struct tablehashcarro {
    Lista_Carros* array_de_listas;
    int tamanho;
}; 
typedef struct tablehashcarro* HashTable_Carros; 

unsigned int hash(char *texto, int tamanho);
HashTable_Carros criar_hashtable_carros(int tamanho);
void inserir_hashtable_carros(HashTable_Carros hashtable, Carro* carro);
Carro* procurar_hashtable_carros(HashTable_Carros hashtable, char* matricula);
void libertar_hashtable_carros(HashTable_Carros hashtable, int libertar_carros);

#endif
