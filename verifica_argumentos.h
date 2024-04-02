#ifndef VERIFICA_ARGUMENTOS_H
#define VERIFICA_ARGUMENTOS_H

#include "bool.h"
#include "lista_parques.h"
#include "hashtable_carros.h"

#define MAX_PARQUES 20 // numero maximo de parques
// Mensagens de erro
#define PARQUE_JA_EXISTE ": parking already exists.\n"
#define CAPACIDADE_INVALIDA ": invalid capacity.\n"
#define CUSTO_INVALIDO "invalid cost.\n"
#define DEMASIADOS_PARQUES "too many parks.\n"
#define PARQUE_INEXISTENTE ": no such parking.\n"
#define PARQUE_CHEIO ": parking is full.\n"
#define MATRICULA_INVALIDA ": invalid licence plate.\n"
#define ENTRADA_INVALIDA ": invalid vehicle entry.\n"
#define DATA_INVALIDA "invalid date.\n"
#define SAIDA_INVALIDA ": invalid vehicle exit.\n"
#define NAO_TEM_ENTRADAS ": no entries found in any parking.\n" 

int verifica_argumentos_p(Lista_Parques lista_parques, char* nome_parque,
                          int capacidade, float valor_15, 
                          float valor_15_apos_1hora, float valor_max_diario);

int verifica_parque_existe(Parque* parque, char* nome_parque);

int verifica_argumentos_e(Parque* parque, char* nome_parque, 
    HashTable_Carros hashtable_carros, Carro** carro, char* matricula, 
    Data* data_entrada, Data* data_sistema);

int verifica_argumentos_s(Parque* parque, char* nome_parque, Carro** carro,
    char* matricula, Registo** registo, Data* data_saida, Data* data_sistema);

int verifica_argumentos_v(Carro* carro, char* matricula);

int verifica_data_f(Data* data, Data* data_sistema);


#endif