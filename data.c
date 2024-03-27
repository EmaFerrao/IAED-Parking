#include <stdio.h> 
#include <stdlib.h>
#include "data.h"
#include "bool.h"

int diasMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Data* cria_data(int ano, int mes, int dia, int hora, int minutos) {
    Data* data = (Data*) malloc(sizeof(Data));
    data->ano = ano;
    data->mes = mes;
    data->dia = dia;
    data->hora = hora;
    data->minutos = minutos;
    return data;
}

int data_valida(Data* data) {
    if (data->ano < 2000) return FALSE;
    if (data->mes < 1 || data->mes > 12) return FALSE;
    if (data->dia < 0 || data->dia > diasMes[data->mes]) return FALSE;
    if (data->hora < 0 || data->hora > 23) return FALSE;
    if (data->minutos < 0 || data->minutos > 59) return FALSE;
    return TRUE;
}

int data_mais_recente(Data* data1, Data* data2) {
    if (data2->ano < data1->ano) return FALSE;
    if (data2->mes < data1->mes) return FALSE;
    if (data2->dia < data1->dia) return FALSE;
    if (data2->hora < data1->hora) return FALSE;
    if (data2->minutos < data1->minutos) return FALSE;
    return TRUE;
}

