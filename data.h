#ifndef DATA_H
#define DATA_H

#define MINUTOS_NUM_DIA 1440    // numero de minutos num dia

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
int total_dias_ano(int ano);
int data_para_minutos(Data* data);
int diferenca_em_minutos(Data* data1, Data* data2);
int mesmo_dia(Data* data1, Data* data2);

#endif