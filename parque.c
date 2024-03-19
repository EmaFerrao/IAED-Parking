/**
 * Todas as funcoes relacionadas com parques.
 * @file parque.c
 * @author ist1109248
*/
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "parque.h"

#define TRUE 1
#define FALSE 0

int caracterbranco(char caracter) {
    if (caracter == ' ') return TRUE;
    if (caracter == '\t') return TRUE;
    return FALSE;
}

void copia_char_incrementa_posicao(char* buffer, char* linha, int* posicao, int* i) {
    buffer[*i] = linha[*posicao];
    (*posicao) += 1;
    (*i) += 1;
}

char* le_nome_parque(char* linha, int* posicao) {
    char buffer[BUFSIZ];
    char* nome;
    int i = 0;
    (*posicao) += 1; //ignora 'p'
    //ignora espacos entre p e nome
    while (caracterbranco(linha[*posicao]) && linha[*posicao] != '\0') {
        (*posicao) += 1;
    }

    if (linha[*posicao] == '"') {
        (*posicao) += 1;
        while (linha[*posicao] != '"' && linha[*posicao] != '\0') {
            copia_char_incrementa_posicao(buffer, linha, posicao, &i);
        }
        (*posicao) += 1;
    } else { 
        while(!caracterbranco(linha[*posicao]) && linha[*posicao] != '\0') {
            copia_char_incrementa_posicao(buffer, linha, posicao, &i);
        }
    }
    buffer[i] = '\0';
    nome = (char*) malloc(sizeof(char)*(strlen(buffer) + 1));
    if (nome != NULL) {
        strcpy(nome, buffer);
    } else {
        printf("Erro na alocação do nome do parque.\n");
        exit(EXIT_FAILURE);
    }
    
    return nome;
}

/* Parque* procura_parque(char* nome){
    Parque_No* aux = parque_head;
    while(aux != NULL){
        if (strcmp(aux->parque->nome, nome) == 0){
            return aux->parque;
        }
        else{
            aux = aux->next;
        }
    }
    return aux;
} */

void le_parque(char* linha) {
    if (strlen(linha)==2) {
        //lista parques
    } else {
        int posicao = 0;
        char* nome_parque;
        int capacidade;
        float valor_15;
        float valor_15_apos_1hora;
        float valor_max_diario;
        int argumentos_recebidos;
        int argumentos_esperados = 4;

        nome_parque = le_nome_parque(linha, &posicao);
        argumentos_recebidos = sscanf(linha+posicao, "%d %f %f %f", &capacidade, &valor_15, &valor_15_apos_1hora, &valor_max_diario);
        if (argumentos_recebidos != argumentos_esperados) {
            printf("Erro a ler argumentos do parque\n");
            exit(EXIT_FAILURE);
        }
        printf("%d %f %f %f", capacidade, valor_15, valor_15_apos_1hora, valor_max_diario);
        
        //cria_parque(); //DEFINIR
    }
}
