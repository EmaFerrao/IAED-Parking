/**
 * Declara as funções que recolhem os argumentos 
 * de linhas de input com diferentes comandos, e o número 
 * de argumentos esperados em cada comando.
 * 
 * @file ler_input.h
 * @author ist1109247
*/
#ifndef LER_INPUT_H
#define LER_INPUT_H

// NÚMERO DE ARGUMENTOS ESPERADOS:
#define ARGS_SO_P 1 // no comando "p", para listar parques
#define ARGS_P_CRIAR_PARQUE 6 // no comando "p", para criar um parque
#define ARGS_E_S 8 // nos comandos "e" e "s"
#define ARGS_V 2 // no comando "v"
#define ARGS_F_COM_DATA 5 // no comando "f", para a faturação de um dia
#define ARGS_F_SEM_DATA 2 // no comando "f", para a faturação de todos os dias
#define ARGS_R 2 // no comando "r"


int le_p(char* linha, char* nome, int* capacidade, float* valor_15, 
         float* valor_15_apos_1hora, float* valor_max_diario);

int le_e_s(char* linha, char* nome_parque, char* matricula, 
           int* dia, int* mes, int* ano, int* hora, int* minutos);

int le_v(char* linha, char* matricula);

int le_f(char* linha, char* nome_parque, int* dia, int* mes, int* ano);

int le_r(char* linha, char* nome_parque);

#endif
