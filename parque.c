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

Parque* procura_parque(char* nome, Parque_No** pp_primeiro_parque){
    if (pp_primeiro_parque == NULL) {
        return NULL;
    }

    Parque_No* aux = (*pp_primeiro_parque);
    while(aux != NULL){
        if (strcmp(aux->parque->nome, nome) == 0){
            return aux->parque;
        }
        aux = aux->next;
    }
    return NULL;
}

void lista_parques(Parque_No** pp_primeiro_parque) {
    if (pp_primeiro_parque == NULL || *pp_primeiro_parque == NULL) {
        printf("no parks to list.\n");
        return;
    }
    Parque_No* aux = (*pp_primeiro_parque);
    while (aux != NULL) {
        Parque* parque = aux -> parque;
        printf("%s %d %d\n", parque->nome, parque->capacidade, parque->lugares_disponiveis);
        if (aux->next == NULL) {
            break;
        }
        aux = aux -> next;
    }
}

void cria_parque(char* nome, int capacidade, float valor_15, float valor_15_apos_1hora, 
    float valor_max_diario, Parque_No** pp_primeiro_parque, Parque_No** pp_ultimo_parque, int *numero_parques) 
    {
        Parque* novo_parque;
        Parque_No* novo_parque_no;

        novo_parque = (Parque*) malloc(sizeof(Parque));
        novo_parque -> nome = nome;
        novo_parque -> capacidade = capacidade;
        novo_parque -> lugares_disponiveis = capacidade;
        novo_parque -> valor_15 = valor_15;
        novo_parque -> valor_15_apos_1hora = valor_15_apos_1hora;
        novo_parque -> valor_max_diario = valor_max_diario;

        novo_parque_no = (Parque_No*) malloc(sizeof(Parque_No));
        novo_parque_no -> parque = novo_parque;
        if ((*pp_ultimo_parque) != NULL) {
            (*pp_ultimo_parque) -> next = novo_parque_no;
        }
        (*pp_ultimo_parque) = novo_parque_no;

        if ((*pp_primeiro_parque) == NULL) {
            (*pp_primeiro_parque) = novo_parque_no;
        }

        (*numero_parques) += 1;
}

void le_parque(char* linha, Parque_No** pp_primeiro_parque, Parque_No** pp_ultimo_parque, int* numero_parques) {
    if (nao_tem_argumentos(linha)) {
        lista_parques(pp_primeiro_parque);   
    } else {
        if ((*numero_parques) == MAX_PARQUES) {
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

        if (procura_parque(nome, pp_primeiro_parque) != NULL) {
            printf("%s: parking already exists.\n", nome);
        } else {
            argumentos_recebidos = sscanf(linha+posicao, "%d %f %f %f", 
            &capacidade, &valor_15, &valor_15_apos_1hora, &valor_max_diario);
            if (argumentos_recebidos != argumentos_esperados) {
                printf("Erro a ler argumentos do parque\n");
            }

            argumentos_validos = verifica_argumentos_parque(capacidade, valor_15, valor_15_apos_1hora, valor_max_diario);
            if (argumentos_validos) {
                cria_parque(nome, capacidade, valor_15, valor_15_apos_1hora, valor_max_diario, pp_primeiro_parque, pp_ultimo_parque, numero_parques);
            }
        }
    }
}
