#ifndef LER_INPUT_H
#define LER_INPUT_H

int le_entrada_ou_saida(char* linha, char* nome_parque, char* matricula, int* dia, int* mes, int* ano, int* hora, int* minutos);
int le_f(char* linha, char* nome_parque, int* dia, int* mes, int* ano);
int le_r(char* linha, char* nome_parque);

#endif