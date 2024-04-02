/**
 * Define os métodos da hashtable de carros.
 * 
 * @file hashtable_carros.c
 * @author ist1109247
*/
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "hashtable_carros.h"

/**
 * @brief Converte uma string num hash.
 * 
 * @param texto 
 * @param tamanho 
 * @return hash 
 */
unsigned int hash(char* texto, int tamanho) {
    unsigned int hash = 7;
    for (int i = 0; texto[i] != '\0'; i++) {
        hash = hash * 31 + texto[i];
    }
    return hash % tamanho;
}

/**
 * @brief Cria uma nova hashtable de carros, que tem 
 * de ser libertada quando deixar de ser utilizada.
 * 
 * @param tamanho 
 * @return hashtable de carros
 */
HashTable_Carros cria_hashtable_carros(int tamanho) {
    if( tamanho <= 100) tamanho = 1000; //evitar hashtables demasiado pequenas
    
    HashTable_Carros hashtable = (HashTable_Carros) malloc(sizeof(struct tablehashcarro));
    hashtable->tamanho = tamanho;
    hashtable->array_de_listas = (Lista_Carros*) malloc(sizeof(Lista_Carros)*(hashtable->tamanho));
    for (int i = 0; i < hashtable->tamanho; i++) {
        hashtable->array_de_listas[i] = cria_lista_carros();
    }
    return hashtable;
} 

/**
 * @brief Insere um carro na hashtable.
 * 
 * @param hashtable 
 * @param carro 
 */
void insere_carro_na_hashtable(HashTable_Carros hashtable, Carro* carro) {
    unsigned int index = hash(carro->matricula, hashtable->tamanho);
    insere_carro_no_fim(hashtable->array_de_listas[index], carro);
}

/**
 * @brief Recebendo uma matrícula, devolve o carro correspondente. 
 * Se não houver um carro com essa matrícula, devolve NULL.
 * 
 * @param hashtable 
 * @param matricula 
 * @return carro 
 */
Carro* procura_carro_na_hashtable(HashTable_Carros hashtable, char* matricula) {
    unsigned int index = hash(matricula, hashtable->tamanho);
    return procura_carro(hashtable->array_de_listas[index], matricula);
}

/**
 * @brief Percorre todos os carros na hashtable e imprime a sua matrícula, 
 * se estão dentro ou fora de um parque e os seus registos.
 * 
 * @param hashtable
 */
void imprime_hashtable_carros(HashTable_Carros hashtable) {
    for (int i=0; i < hashtable->tamanho; i++) {
        itera_lista_carros(hashtable->array_de_listas[i], imprime_carro_tudo);
    }
}

/**
 * @brief Liberta a memória da hashtable, podendo ou não libertar os carros.
 * 
 * @param hashtable 
 * @param libertar_carros TRUE ou FALSE
 */
void liberta_hashtable_carros(HashTable_Carros hashtable, int libertar_carros) {
    for (int i = 0; i < hashtable->tamanho; i++) {
        liberta_lista_carros(hashtable->array_de_listas[i], libertar_carros);
    }
    free(hashtable->array_de_listas);
    free(hashtable);
}

