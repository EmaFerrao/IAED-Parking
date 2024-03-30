#include <stdio.h> 
#include "ler_input.h"
#include "bool.h"

int le_entrada_ou_saida(char* linha, char* nome_parque, char* matricula, int* dia, int* mes, int* ano, int* hora, int* minutos) {
    char comando;
    int argumentos_recebidos;
    int argumentos_esperados = 8;

    argumentos_recebidos = sscanf(linha, "%c \"%[^\"]\" %s %d-%d-%d %d:%d", &comando, 
        nome_parque, matricula, dia, mes, ano, hora, minutos);
    if (argumentos_recebidos != argumentos_esperados) {

        argumentos_recebidos = sscanf(linha, "%c %s %s %d-%d-%d %d:%d", &comando, 
        nome_parque, matricula, dia, mes, ano, hora, minutos);
        if (argumentos_recebidos != argumentos_esperados) {
            printf("Erro a ler entrada.\n");
            return FALSE;
        }
    }
    return TRUE;
}

int le_f(char* linha, char* nome_parque, int* dia, int* mes, int* ano) {
    char comando;
    int argumentos_recebidos;

    argumentos_recebidos = sscanf(linha, "%c \"%[^\"]\" %d-%d-%d", &comando, nome_parque, dia, mes, ano);
    if (argumentos_recebidos == 1) {
        argumentos_recebidos = sscanf(linha, "%c %s %d-%d-%d", &comando, nome_parque, dia, mes, ano);
        if (argumentos_recebidos != 5 && argumentos_recebidos != 2) {
            printf("Erro a ler entrada.\n");
        }
    }
    return argumentos_recebidos;
}

int le_r(char* linha, char* nome_parque) {
    char comando;
    int argumentos_recebidos;
    int argumentos_esperados = 2;

    argumentos_recebidos = sscanf(linha, "%c \"%[^\"]\"", &comando, 
        nome_parque);
    if (argumentos_recebidos != argumentos_esperados) {

        argumentos_recebidos = sscanf(linha, "%c %s", &comando, 
        nome_parque);
        if (argumentos_recebidos != argumentos_esperados) {
            printf("Erro a ler entrada.\n");
            return FALSE;
        }
    }
    return TRUE;
}