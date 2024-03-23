#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "parque.h"
#include "carro.h"

#define FALSE 0
#define TRUE 1
#define TAMANHO_MATRICULA 9

//void registar_entrada(char* linha, Parque_No** head_parques, int* numero_parques)
void registar_entrada(char* linha) {
    char* matricula =  NULL;
    char* nome_parque = NULL;
    int* data = NULL;
    ler_entrada(linha, matricula, nome_parque, data);
}

void ler_entrada(char* linha, char* matricula, char* nome_parque, int* data) {
    int ano, mes, dia, hora, minutos, arg;
    char comando_ignorar;
    arg = sscanf(linha, "%c %s %s %d-%d-%d %d:%d", &comando_ignorar, nome_parque, matricula, &dia, &mes, &ano, &hora, &minutos);
    *data = ano;
    printf("%d", arg);
    printf("%s %s %d-%d-%d %d:%d", nome_parque, matricula, dia, mes, ano, hora, minutos);
}