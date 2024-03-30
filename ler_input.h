#ifndef LER_INPUT_H
#define LER_INPUT_H

int le_p(char* linha, char* nome, int* capacidade, float* valor_15, float* valor_15_apos_1hora, float* valor_max_diario);
int le_e_s(char* linha, char* nome_parque, char* matricula, int* dia, int* mes, int* ano, int* hora, int* minutos);
int le_v(char* linha, char* matricula);
int le_f(char* linha, char* nome_parque, int* dia, int* mes, int* ano);
int le_r(char* linha, char* nome_parque);

#endif