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

char* le_nome_parque(char* linha, int* posicao) {
    char buffer[BUFSIZ];
    char* nome;
    int i = 0;
    (*posicao) += 1; //ignora 'p'
    while (caracterbranco(linha[*posicao]) && linha[*posicao] != '\0') {
        (*posicao) += 1;
    }

    if (linha[*posicao] == '"') {
        (*posicao) += 1;
        while (linha[*posicao] != '"' && linha[*posicao] != '\0') {
            buffer[i] = linha[*posicao];
            (*posicao) += 1;
            i += 1;
        }
        (*posicao) += 1;
    } else { 
        while(!caracterbranco(linha[*posicao]) && linha[*posicao] != '\0') {
            buffer[i] = linha[*posicao];
            (*posicao) += 1;
            i += 1;
        }
    }
    buffer[i] = '\0';
    nome = (char*) malloc(sizeof(char)*(strlen(buffer) + 1));
    strcpy(nome, buffer);
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
        nome_parque = le_nome_parque(linha, &posicao);
        printf("%d\n", posicao);
        printf("%s\n", linha + posicao);
        sscanf(linha+posicao, "%d %f %f %f", &capacidade, &valor_15, &valor_15_apos_1hora, &valor_max_diario);
        printf("%d %f %f %f", capacidade, valor_15, valor_15_apos_1hora, valor_max_diario);
        //cria_parque(); //DEFINIR
    }
}
