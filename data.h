#ifndef DATA_H
#define DATA_H

typedef struct {
    int ano;
    int mes;
    int dia;
    int hora;
    int minutos;
} Data;

Data* cria_data(int ano, int mes, int dia, int hora, int minutos);
int data_valida(Data* datahora);
int data_mais_recente(Data* datahora_1, Data* datahora_2);
int verifica_data(Data* datahora_sistema, Data* datahora);

#endif