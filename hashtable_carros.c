#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "hashtable_carros.h"

unsigned int hash(char *texto, int tamanho) {
    unsigned int hash = 7;
    for (int i = 0; texto[i] != '\0'; i++) {
        hash = hash * 31 + texto[i];
    }
    return hash % tamanho;
}

HashTable_Carros criar_hashtable_carros(int tamanho) {
    if( tamanho <= 100) tamanho = 1000; //evitar hashtables demasiado pequenas
    
    HashTable_Carros hashtable = (HashTable_Carros) malloc(sizeof(struct tablehashcarro));
    hashtable->tamanho = tamanho;
    hashtable->array_de_listas = (Lista_Carros*) malloc(sizeof(Lista_Carros)*(hashtable->tamanho));
    for (int i = 0; i < hashtable->tamanho; i++) {
        hashtable->array_de_listas[i] = cria_lista_carros();
    }
    return hashtable;
} 

void inserir_hashtable_carros(HashTable_Carros hashtable, Carro* carro) {
    unsigned int index = hash(carro->matricula, hashtable->tamanho);
    insere_carro_no_fim(hashtable->array_de_listas[index], carro);
}

Carro* procurar_hashtable_carros(HashTable_Carros hashtable, char* matricula) {
    unsigned int index = hash(matricula, hashtable->tamanho);
    return procura_carro(hashtable->array_de_listas[index], matricula);
}

void imprime_hashtable_carros(HashTable_Carros hashtable) {
    for (int i=0; i < hashtable->tamanho; i++) {
        itera_lista_carros(hashtable->array_de_listas[i], imprime_carro_tudo);
    }
}

void libertar_hashtable_carros(HashTable_Carros hashtable, int libertar_carros) {
    for (int i = 0; i < hashtable->tamanho; i++) {
        libertar_lista_carros(hashtable->array_de_listas[i], libertar_carros);
    }
    free(hashtable->array_de_listas);
    free(hashtable);
}




