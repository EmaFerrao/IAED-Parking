#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "carro.h"

#define FALSE 0
#define TRUE 1
#define TAMANHO_MATRICULA 9
#define TAMANHO_DATA 9
#define TAMANHO_HORA 6

void comando_e(char* linha, Lista_Parques lista_parques, HashTable_Carros hashtable_carros) {
    char nome_parque[MAX_NOME_PARQUE];
    char matricula[TAMANHO_MATRICULA];
    char data[TAMANHO_DATA];
    char hora[TAMANHO_HORA];
    Carro* carro;
    if (!le_entrada_ou_saida(linha, nome_parque, matricula, data, hora)) {
        return;
    }
    carro = procurar_hashtable_carros(hashtable_carros, matricula);
    if (carro == NULL) {
        carro = cria_carro(matricula);
        inserir_hashtable_carros(hashtable_carros, carro);
    }
    
}

int le_entrada_ou_saida(char* linha, char* nome_parque, char* matricula, char* data, char* hora) {
    char comando;
    int argumentos_recebidos;
    int argumentos_esperados = 5;

    argumentos_recebidos = sscanf(linha, "%c \"%[^\"]\" %s %s %s", &comando, 
        nome_parque, matricula, data, hora);
    if (argumentos_recebidos != argumentos_esperados) {

        argumentos_recebidos = sscanf(linha, "%c %s %s %s %s", &comando, 
        nome_parque, matricula, data, hora);
        if (argumentos_recebidos != argumentos_esperados) {
            printf("Erro a ler entrada.\n");
            return FALSE;
        }
    }
    return TRUE;
} 

Carro* cria_carro(char* matricula) {
    Carro* carro = (Carro*) malloc(sizeof(Carro));
    carro->matricula = matricula;
    carro->lista_registos = cria_lista_registos();
    return carro;
}

void libertar_carro(Carro* carro) {
    int libertar_registos = TRUE;
    libertar_lista_registos(carro->lista_registos, libertar_registos);
    free(carro);
}