/**
 * Declara a estrutura de uma data e os seus métodos. 
 * Define constantes relacionadas com datas.
 * 
 * @file data.h
 * @author ist1109247
*/
#ifndef DATA_H
#define DATA_H

#define MINUTOS_NUM_DIA 1440 // número de minutos num dia

#define ANO_DEFAULT 2000 // ano da data default do sistema
#define MES_DEFAULT 1 // mês da data default do sistema
#define DIA_DEFAULT 1 // dia da data default do sistema
#define HORA_DEFAULT 0 // hora da data default do sistema
#define MINUTO_DEFAULT 0 // minuto da data default do sistema

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
