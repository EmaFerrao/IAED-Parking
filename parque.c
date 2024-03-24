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
#define MAX_PARQUES 20
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

int verifica_argumentos_parque(int capacidade, float valor_15, float valor_15_apos_1hora, float valor_max_diario) {
    int valores_certos = TRUE;
    int valido = TRUE;

    if (capacidade <= 0) {
        printf("%d: invalid capacity.\n", capacidade);
        valido = FALSE;
        return valido;
    }

    if (valor_15 <= 0 || valor_15_apos_1hora <= 0 || valor_max_diario <= 0) {
        valores_certos = FALSE;
    }

    if (!(valor_15 < valor_15_apos_1hora && valor_15_apos_1hora < valor_max_diario)) {
        valores_certos = FALSE;
    }

    if (! valores_certos) {
        printf("invalid cost.\n");
    }
    return valores_certos;
}

void cria_parque(char* nome, int capacidade, float valor_15, float valor_15_apos_1hora, 
    float valor_max_diario, Lista_Parques lista_parques) 
    {
        Parque* parque;

        parque = (Parque*) malloc(sizeof(Parque));
        parque -> nome = strdup(nome);
        parque -> capacidade = capacidade;
        parque -> lugares_disponiveis = capacidade;
        parque -> valor_15 = valor_15;
        parque -> valor_15_apos_1hora = valor_15_apos_1hora;
        parque -> valor_max_diario = valor_max_diario;

        append_Lista_Parques(lista_parques, parque);
}

void imprime_parque(Parque* parque) {
    printf("%s %d %d\n", parque->nome, parque->capacidade, parque->lugares_disponiveis);
}

void libertar_parque(Parque* parque) {
    free(parque->nome);
    free(parque);
}

void le_parque(char* linha, Lista_Parques lista_parques) {
    if (nao_tem_argumentos(linha)) {
        imprime_lista_parques(lista_parques);   
    } else {
        if (lista_parques->numero_parques == MAX_PARQUES) {
            printf("too many parks.\n");
            return;
        }

        int posicao = 0;
        char* nome;
        int capacidade;
        float valor_15;
        float valor_15_apos_1hora;
        float valor_max_diario;
        int argumentos_recebidos;
        int argumentos_esperados = 4;
        int argumentos_validos = TRUE;

        nome = le_nome_parque(linha, &posicao);

        if (procura_parque(nome, lista_parques) != NULL) {
            printf("%s: parking already exists.\n", nome);
        } else {
            argumentos_recebidos = sscanf(linha+posicao, "%d %f %f %f", 
            &capacidade, &valor_15, &valor_15_apos_1hora, &valor_max_diario);
            if (argumentos_recebidos != argumentos_esperados) {
                printf("Erro a ler argumentos do parque\n");
            }

            argumentos_validos = verifica_argumentos_parque(capacidade, valor_15, valor_15_apos_1hora, valor_max_diario);
            if (argumentos_validos) {
                cria_parque(nome, capacidade, valor_15, valor_15_apos_1hora, valor_max_diario, lista_parques);
            }
        }
        free(nome);
    }
}



