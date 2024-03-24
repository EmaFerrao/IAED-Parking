#ifndef CARRO_H
#define CARRO_H

#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "registo.h"
#include "parque.h"

typedef struct {
    char* matricula;
    Lista_Registos lista_registos;
} Carro;

typedef struct carro_node{
    Carro* carro;
    struct carro_node* next;
} Carro_Node;

struct carros_lista{
    Carro_Node* head;
    Carro_Node* tail;
};
typedef struct carros_lista* Lista_Carros;

typedef void (*Operacao_Carro)(Carro*);

struct tablehashcarro {
    Lista_Carros* array_de_listas;
    int tamanho;
}; 
typedef struct tablehashcarro* HashTable_Carros; 


void comando_e(char* linha, Lista_Parques lista_parques, HashTable_Carros hashtable_carros);
int le_entrada_ou_saida(char* linha, char* nome_parque, char* matricula, char* data, char* hora);

Carro* cria_carro(char* matricula);
void libertar_carro(Carro* carro);

//Lista
Lista_Carros cria_lista_carros();
void itera_lista_carros(Lista_Carros lista_carros, Operacao_Carro operacao);
Carro* procura_carro(Lista_Carros lista_carros, char* matricula);
void append_lista_carros(Lista_Carros lista_carros, Carro* carro);
void libertar_lista_carros(Lista_Carros lista_carros, int libertar_carros);

//Hashtable
int hash(char *texto, int tamanho);
HashTable_Carros criar_hashtable_carros(int tamanho_esperado);
void inserir_hashtable_carros(HashTable_Carros hashtable, Carro* carro);

#endif
