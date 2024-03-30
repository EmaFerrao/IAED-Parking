#include <stdio.h> 
#include "ler_input.h"
#include "bool.h"

int le_p(char* linha, char* nome, int* capacidade, float* valor_15, float* valor_15_apos_1hora, float* valor_max_diario) {
    char comando;
    int argumentos_so_p = 1, argumentos_esperados = 6;
    int argumentos_recebidos;

    argumentos_recebidos = sscanf(linha, "%c \"%[^\"]\" %d %f %f %f", &comando, 
        nome, capacidade, valor_15, valor_15_apos_1hora, valor_max_diario);

    if (argumentos_recebidos != argumentos_esperados) {
        argumentos_recebidos = sscanf(linha, "%c %s %d %f %f %f", &comando, 
            nome, capacidade, valor_15, valor_15_apos_1hora, valor_max_diario);

        if (argumentos_recebidos != argumentos_esperados && argumentos_recebidos != argumentos_so_p) {
            return FALSE;
        }
    }
    return argumentos_recebidos;
}

int le_e_s(char* linha, char* nome_parque, char* matricula, int* dia, int* mes, int* ano, int* hora, int* minutos) {
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

int le_v(char* linha, char* matricula) {
    char comando;
    int argumentos_esperados = 2;
    int argumentos_recebidos;

    argumentos_recebidos = sscanf(linha, "%c %s", &comando, matricula);
    if (argumentos_recebidos != argumentos_esperados) {
        return FALSE;
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
            return FALSE;
        }
    }
    return TRUE;
}