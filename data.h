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
int data_mais_recente(Data* data1, Data* data2);
int mesmo_dia(Data* data1, Data* data2);
int conta_dias(Data* entrada, Data* saida);

#endif