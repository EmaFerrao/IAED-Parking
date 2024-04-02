/**
 * Define os métodos das datas.
 * 
 * @file data.c
 * @author ist1109247
*/
#include <stdio.h> 
#include <stdlib.h>
#include "data.h"
#include "bool.h"

/**
 * @brief Cria e devolve uma nova data, que tem de ser 
 * libertada quando deixar de ser utilizada.
 */
Data* cria_data(int ano, int mes, int dia, int hora, int minutos) {
    Data* data = (Data*) malloc(sizeof(Data));
    data->ano = ano;
    data->mes = mes;
    data->dia = dia;
    data->hora = hora;
    data->minutos = minutos;
    return data;
}

/**
 * @brief Devolve o número de dias no mês recebido.
 */
int dias_no_mes(int mes) {
    int dias_mes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return dias_mes[mes];
}

/**
 * @brief Verifica se a data é válida..
 */
int data_valida(Data* data) {
    if (data->ano < 2000) return FALSE;
    if (data->mes < 1 || data->mes > 12) return FALSE;
    if (data->dia < 0 || data->dia > dias_no_mes(data->mes)) return FALSE;
    if (data->hora < 0 || data->hora > 23) return FALSE;
    if (data->minutos < 0 || data->minutos > 59) return FALSE;
    return TRUE;
}

/**
 * @brief Verifica se a data do segundo argumento 
 * é mais recente do que a data do primeiro.
 */
int data_mais_recente(Data* data1, Data* data2) {
    if (data2->ano != data1->ano)
        return data2->ano > data1->ano;
    if (data2->mes != data1->mes)
        return data2->mes > data1->mes;
    if (data2->dia != data1->dia)
        return data2->dia > data1->dia;
    if (data2->hora != data1->hora)
        return data2->hora > data1->hora;
    return data2->minutos >= data1->minutos;
}


/**
 * @brief Devolve o número de dias desde o ano 0 até ao ano recebido.
 */
int total_dias_ano(int ano) {
    return 365 * ano - ano / 100 + ano / 400;
}

/**
 * @brief Devolve o número de minutos desde 00-00-0000 00:00 
 * até à data recebida.
 */
int data_para_minutos(Data* data) {
    int minutos = 0;

    minutos += total_dias_ano(data->ano - 1) * MINUTOS_NUM_DIA;
    
    for (int mes = 1; mes < data->mes; mes++) {
        minutos += dias_no_mes(mes) * MINUTOS_NUM_DIA;
    }
    minutos += (data->dia - 1) * MINUTOS_NUM_DIA;
    minutos += data->hora * 60;
    minutos += data->minutos;
    return minutos;
}

/**
 * @brief Devolve o número de minutos entre as datas recebidas.
 */
int diferenca_em_minutos(Data* data1, Data* data2) {
    return data_para_minutos(data2) - data_para_minutos(data1);
}

/**
 * @brief Verifica se as datas são no mesmo 
 * dia, do mesmo mês e do mesmo ano.
 */
int mesmo_dia(Data* data1, Data* data2) {
    if (data1->ano != data2->ano) return FALSE;
    if (data1->mes != data2->mes) return FALSE;
    if (data1->dia != data2->dia) return FALSE;
    return TRUE;
}
