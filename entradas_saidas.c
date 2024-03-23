#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "parque.h"
#include "carro.h"

#define FALSE 0
#define TRUE 1
#define TAMANHO_MATRICULA 9

int cria_data(int dia, int mes, int ano, int hora, int minutos) {
    return minutos + hora*100 + dia*10000 + mes*1000000 + ano*100000000;
}

//void registar_entrada(char* linha, Parque_No** head_parques, int* numero_parques)
void registar_entrada(char* linha) {
    char matricula[TAMANHO_MATRICULA];
    char nome_parque[BUFSIZ];
    int data;
    ler_entrada(linha, matricula, nome_parque, &data);
    printf("%s %s %d\n", nome_parque, matricula, data);

}

void ler_entrada(char* linha, char* matricula, char* nome_parque, int* data) {
    int ano, mes, dia, hora, minutos;
    int argumentos_esperados = 8;
    int argumentos_recebidos;
    char comando_ignorar;

    argumentos_recebidos = sscanf(linha, "%c %s %s %d-%d-%d %d:%d", 
    &comando_ignorar, nome_parque, matricula, &dia, &mes, &ano, &hora, &minutos);
    if (argumentos_recebidos != argumentos_esperados) {
        printf("erro a ler entrada.\n");
    }
    *data = cria_data(dia, mes, ano, hora, minutos);
}