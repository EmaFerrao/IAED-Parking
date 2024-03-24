#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "input.h"

#define TRUE 1
#define FALSE 0
#define BUFSIZE 8192

int nao_tem_argumentos(char* linha) {
    return strlen(linha)==2;
}

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
    char buffer[BUFSIZE];
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
    }
    
    return nome;
}