#include <stdio.h> 
#include "ler_input.h"
#include "bool.h"

int le_p(char* linha, char* nome_parque, int* capacidade, float* valor_15, float* valor_15_apos_1hora, float* valor_max_diario) {
    char comando;
    int argumentos_recebidos;

    argumentos_recebidos = sscanf(linha, "%c \"%[^\"]\" %d %f %f %f", &comando, 
        nome_parque, capacidade, valor_15, valor_15_apos_1hora, 
        valor_max_diario);

    if (argumentos_recebidos != ARGS_P_CRIAR_PARQUE) {
        argumentos_recebidos = sscanf(linha, "%c %s %d %f %f %f", &comando, 
            nome_parque, capacidade, valor_15, valor_15_apos_1hora, 
            valor_max_diario);

        if (argumentos_recebidos != ARGS_P_CRIAR_PARQUE && 
            argumentos_recebidos != ARGS_SO_P) {
            return FALSE;
        }
    }
    return argumentos_recebidos;
}

int le_e_s(char* linha, char* nome_parque, char* matricula, int* dia, int* mes, int* ano, int* hora, int* minutos) {
    char comando;
    int argumentos_recebidos;

    argumentos_recebidos = sscanf(linha, "%c \"%[^\"]\" %s %d-%d-%d %d:%d", &comando, 
        nome_parque, matricula, dia, mes, ano, hora, minutos);
    if (argumentos_recebidos != ARGS_E_S) {

        argumentos_recebidos = sscanf(linha, "%c %s %s %d-%d-%d %d:%d", &comando, 
        nome_parque, matricula, dia, mes, ano, hora, minutos);
        if (argumentos_recebidos != ARGS_E_S) {
            return FALSE;
        }
    }
    return TRUE;
}

int le_v(char* linha, char* matricula) {
    char comando;
    int argumentos_recebidos;

    argumentos_recebidos = sscanf(linha, "%c %s", &comando, matricula);
    if (argumentos_recebidos != ARGS_V) {
        return FALSE;
    }
    return TRUE;
}

int le_f(char* linha, char* nome_parque, int* dia, int* mes, int* ano) {
    char comando;
    int argumentos_recebidos;

    argumentos_recebidos = sscanf(linha, "%c \"%[^\"]\" %d-%d-%d", &comando, 
        nome_parque, dia, mes, ano);
    if (argumentos_recebidos != ARGS_F_COM_DATA && 
        argumentos_recebidos != ARGS_F_SEM_DATA) {

        argumentos_recebidos = sscanf(linha, "%c %s %d-%d-%d", &comando, nome_parque, dia, mes, ano);
        if (argumentos_recebidos != ARGS_F_COM_DATA && 
            argumentos_recebidos != ARGS_F_SEM_DATA) {
            return FALSE;
        }
    }
    return argumentos_recebidos;
}

int le_r(char* linha, char* nome_parque) {
    char comando;
    int argumentos_recebidos;

    argumentos_recebidos = sscanf(linha, "%c \"%[^\"]\"", &comando, 
        nome_parque);
    if (argumentos_recebidos != ARGS_R) {

        argumentos_recebidos = sscanf(linha, "%c %s", &comando, 
        nome_parque);
        if (argumentos_recebidos != ARGS_R) {
            return FALSE;
        }
    }
    return TRUE;
}