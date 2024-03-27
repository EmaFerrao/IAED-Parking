#include <stdio.h> 
#include <stdlib.h>
#include "datahora.h"
#include "bool.h"

int diasMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

DataHora* cria_data(int dia, int mes, int ano, int hora, int minutos) {
    DataHora* datahora = (DataHora*) malloc(sizeof(DataHora));
    datahora->dia = dia;
    datahora->mes = mes;
    datahora->ano = ano;
    datahora->hora = hora;
    datahora->minutos = minutos;
    return datahora;
}

int data_valida(DataHora* datahora) {
    if (datahora->ano < 0) return FALSE;
    if (datahora->mes < 1 || datahora->mes > 12) return FALSE;
    if (datahora->dia < 0 || datahora->dia > diasMes[datahora->mes]) return FALSE;
    if (datahora->hora < 0 || datahora->hora > 23) return FALSE;
    if (datahora->minutos < 0 || datahora->minutos > 59) return FALSE;
    return TRUE;
}

int data_mais_recente(DataHora* datahora_1, DataHora* datahora_2) {
    if (datahora_2->ano < datahora_1->ano) return FALSE;
    if (datahora_2->mes < datahora_1->mes) return FALSE;
    if (datahora_2->dia < datahora_1->dia) return FALSE;
    if (datahora_2->hora < datahora_1->hora) return FALSE;
    if (datahora_2->minutos < datahora_1->minutos) return FALSE;
    return TRUE;
}
