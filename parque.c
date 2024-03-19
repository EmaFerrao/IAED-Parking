#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "parque.h"

#define TRUE 1
#define FALSE 0

Parque_No *parque_head = NULL;

int caracterbranco(char caracter){
    if (caracter == ' ') return TRUE;
    if (caracter == '\t') return TRUE;
    return FALSE;
}

char* le_nome_parque(char* linha){
    char buffer[BUFSIZ];
    char* nome;
    int i=0;
    linha++; //ignora 'p'
    while (*linha != '"' && caracterbranco(*linha)){
        linha++;
    }
    // nome entre aspas
    if (*linha == '"'){
        linha++;
        while (*linha != '"'){
            buffer[i++] = *linha++;
        }
    }
    // não está entre aspas
    else {
        while(!caracterbranco(*linha) && *linha != '\0'){
            buffer[i++] = *linha++;
        }
    }
    i++;
    buffer[i] = '\0';
    nome = (char*)(malloc(sizeof(char)*(strlen(buffer) + 1)));
    printf("%lu\n",strlen(buffer));
    strcpy(nome, buffer);
    printf("%lu\n",strlen(nome));
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

void le_parque(char* linha){
    if (strlen(linha)==2){
        //lista parques
    }
    else{
        char buffer[BUFSIZ];
        char* nome_parque;
        int capacidade;
        float valor_15;
        float valor_15_apos_1hora;
        float valor_max_diario;
        nome_parque = le_nome_parque(linha);
        printf("%s\n", nome_parque);
        //cria_parque(); //DEFINIR
    }
}
