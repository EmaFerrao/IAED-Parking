#ifndef DATAHORA_H
#define DATAHORA_H

typedef struct {
    int dia;
    int mes;
    int ano;
    int hora;
    int minutos;
} DataHora;

DataHora* cria_data(int dia, int mes, int ano, int hora, int minutos);
int data_valida(DataHora* datahora);
int data_mais_recente(DataHora* datahora_1, DataHora* datahora_2);

#endif