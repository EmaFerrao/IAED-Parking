#ifndef VERIFICA_ARGUMENTOS_H
#define VERIFICA_ARGUMENTOS_H

#include "bool.h"
#include "lista_parques.h"
#include "hashtable_carros.h"

#define MAX_PARQUES 20 // numero maximo de parques

int verifica_argumentos_p(Lista_Parques lista_parques, char* nome_parque,
    int capacidade, float valor_15, float valor_15_apos_1hora, float valor_max_diario);
int verifica_parque_existe(Parque* parque, char* nome_parque);
int verifica_argumentos_e(Parque* parque, char* nome_parque, 
    HashTable_Carros hashtable_carros, Carro** carro, char* matricula, 
    Data* data_entrada, Data* data_sistema);
int verifica_argumentos_s(Parque* parque, char* nome_parque, Carro** carro,
    char* matricula, Registo** registo, Data* data_saida, Data* data_sistema);
int verifica_argumentos_v(Carro* carro, char* matricula);
int verifica_argumentos_f(Data* data, Data* data_sistema);

#endif