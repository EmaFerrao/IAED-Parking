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

int mesmo_dia(Data* data1, Data* data2) {
    if (data1->ano != data2->ano) return FALSE;
    if (data1->mes != data2->mes) return FALSE;
    if (data1->dia != data2->dia) return FALSE;
    return TRUE;
}

int conta_dias(Data* entrada, Data* saida) {
    int dias = 0;
    dias += (saida->ano - entrada->ano) * 365;
    if (entrada->mes == saida->mes) {
        dias += saida->dia -1 - entrada->dia;
    } else {
        dias += diasMes[entrada->dia] - entrada->dia;
        for (int i=entrada->mes+1; i<saida->mes; i++) {
            dias += diasMes[i];
        }
        dias += saida->dia -1;
    }
    return dias;
}