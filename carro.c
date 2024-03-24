#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "carro.h"

#define FALSE 0
#define TRUE 1
#define TAMANHO_MATRICULA 9

long int cria_data(int dia, int mes, int ano, int hora, int minutos) {
    long int data = 0;
    data += minutos;
    data += hora*100;
    data += dia*10000;
    data += mes*1000000;
    data += (long int)ano*100000000;
    return data;
}

void comando_e(char* linha, Lista_Parques lista_parques, HashTable_Carros hashtable_carros) {
    char nome_parque[BUFSIZ];
    char matricula[TAMANHO_MATRICULA];
    long int data;
    le_entrada_ou_saida(linha, nome_parque, matricula, &data);
    printf("%s %s %lu\n", nome_parque, matricula, data);

}

void le_entrada_ou_saida(char* linha, char* nome_parque, char* matricula, long int* data) {
    int posicao = 0;
    int ano, mes, dia, hora, minutos;
    int argumentos_esperados = 6;
    int argumentos_recebidos;

    nome_parque = le_nome_parque(linha, &posicao);

    argumentos_recebidos = sscanf(linha+posicao, "%s %d-%d-%d %d:%d", matricula, &dia, &mes, &ano, &hora, &minutos);
    if (argumentos_recebidos != argumentos_esperados) {
        printf("erro a ler entrada.\n");
    }
    *data = cria_data(dia, mes, ano, hora, minutos);
}

Carro* cria_carro(char* matricula) {
    Carro* carro = (Carro*) malloc(sizeof(Carro));
    carro->matricula = matricula;
    carro->lista_registos = cria_lista_registos();
    return carro;
}

void libertar_carro(Carro* carro) {
    int libertar_registos = TRUE;
    libertar_lista_registos(carro->lista_registos, libertar_registos);
    free(carro);
}