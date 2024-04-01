#ifndef LER_INPUT_H
#define LER_INPUT_H

#define ARGS_SO_P 1              // numero de argumentos no comando "p", quando e para listar parques
#define ARGS_P_CRIAR_PARQUE 6    // numero de argumentos no comando "p", quando e para criar um parque
#define ARGS_E_S 8               // numero de argumentos nos comandos "e" e "s"
#define ARGS_V 2                 // numero de argumentos no comando "v"
#define ARGS_F_COM_DATA 5        // numero de argumentos no comando "f", quando e para mostrar faturacao de so um dia
#define ARGS_F_SEM_DATA 2        // numero de argumentos no comando "f", quando e para mostrar faturacao de todos os dias
#define ARGS_R 2                 // numero de argumentos no comando "r"

int le_p(char* linha, char* nome, int* capacidade, float* valor_15, float* valor_15_apos_1hora, float* valor_max_diario);
int le_e_s(char* linha, char* nome_parque, char* matricula, int* dia, int* mes, int* ano, int* hora, int* minutos);
int le_v(char* linha, char* matricula);
int le_f(char* linha, char* nome_parque, int* dia, int* mes, int* ano);
int le_r(char* linha, char* nome_parque);

#endif