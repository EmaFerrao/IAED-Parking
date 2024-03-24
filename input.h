#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>

int nao_tem_argumentos(char* linha);
int caracterbranco(char caracter);
void copia_char_incrementa_posicao(char* buffer, char* linha, int* posicao, int* i);
char* le_nome_parque(char* linha, int* posicao);