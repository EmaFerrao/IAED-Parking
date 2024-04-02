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
 * @brief Cria uma nova data, que tem de ser 
 * libertada quando deixar de ser utilizada.
 * 
 * @param ano 
 * @param mes 
 * @param dia 
 * @param hora 
 * @param minutos 
 * @return Data* 
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
 * @brief Devolve o número de dias num dado mês.
 * 
 * @param mes 
 * @return número de dias
 */
int dias_no_mes(int mes) {
    int diasMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return diasMes[mes];
}

/**
 * @brief Devolve TRUE se receber uma data válida e FALSE caso contrário.
 * 
 * @param data 
 * @return TRUE ou FALSE
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
 * @brief Devolve TRUE se a data do segundo argumento 
 * for mais recente do que a data do primeiro e FALSE
 * caso contrário.
 * 
 * @param data1 
 * @param data2 
 * @return TRUE ou FALSE
 */
int data_mais_recente(Data* data1, Data* data2) {
    if (data2->ano < data1->ano) return FALSE;
    if (data2->ano > data1->ano) return TRUE;
    if (data2->mes < data1->mes) return FALSE;
    if (data2->mes > data1->mes) return TRUE;
    if (data2->dia < data1->dia) return FALSE;
    if (data2->dia > data1->dia) return TRUE;
    if (data2->hora < data1->hora) return FALSE;
    if (data2->hora > data1->hora) return TRUE;
    if (data2->minutos < data1->minutos) return FALSE;
    return TRUE;
}

/**
 * @brief Devolve o número de dias desde o ano 0 até ao ano recebido.
 * 
 * @param ano 
 * @return número de dias
 */
int total_dias_ano(int ano) {
    return 365 * ano - ano / 100 + ano / 400;
}

/**
 * @brief Devolve o número de minutos desde 00-00-0000 00:00 
 * até à data recebida.
 * 
 * @param data 
 * @return número de minutos
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
 * 
 * @param data1 
 * @param data2 
 * @return número de minutos
 */
int diferenca_em_minutos(Data* data1, Data* data2) {
    return data_para_minutos(data2) - data_para_minutos(data1);
}

/**
 * @brief Devolve TRUE se as datas forem no mesmo dia, 
 * do mesmo mês, do mesmo ano e FALSE caso contrário.
 * 
 * @param data1 
 * @param data2 
 * @return TRUE ou FALSE 
 */
int mesmo_dia(Data* data1, Data* data2) {
    if (data1->ano != data2->ano) return FALSE;
    if (data1->mes != data2->mes) return FALSE;
    if (data1->dia != data2->dia) return FALSE;
    return TRUE;
}