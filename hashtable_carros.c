#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "hashtable_carros.h"

int hash(char *texto, int tamanho) {
    int hash = 7;
    for (int i = 0; texto[i] != '\0'; i++) {
        hash = hash*31 + texto[i];
    }
    return hash % tamanho;
}

HashTable_Carros criar_hashtable_carros(int tamanho_esperado) {
    int numero_entradas_por_lista = 10;
    if( tamanho_esperado <= 100) tamanho_esperado = 1000; //evitar hashtables demasiado pequenas

    HashTable_Carros hashtable = (HashTable_Carros) malloc(sizeof(HashTable_Carros));
    hashtable->tamanho = tamanho_esperado / numero_entradas_por_lista;
    hashtable->array_de_listas = (Lista_Carros*) malloc(sizeof(Lista_Carros)*hashtable->tamanho);
    for (int i = 0; i < hashtable->tamanho; i++) {
        hashtable->array_de_listas[i] = cria_lista_carros();
    }
    return hashtable;
} 

void inserir_hashtable_carros(HashTable_Carros hashtable, Carro* carro) {
    int index = hash(carro->matricula, hashtable->tamanho);
    append_lista_carros(hashtable->array_de_listas[index], carro);
}

Carro* procurar_hashtable_carros(HashTable_Carros hashtable, char* matricula) {
    int index = hash(matricula, hashtable->tamanho);
    return procura_carro(hashtable->array_de_listas[index], matricula);
}

void libertar_hashtable_carros(HashTable_Carros hashtable, int libertar_carros) {
    for (int i=0; i < hashtable->tamanho; i++) {
        libertar_lista_carros(hashtable->array_de_listas[i], libertar_carros);
        printf("%d", i);
    }
    free(hashtable->array_de_listas);
    free(hashtable);
}




