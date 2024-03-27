#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "comandos.h"
#include "bool.h"
#include "hashtable_carros.h"

#define MAX_PARQUES 20
#define TAMANHO_ARGUMENTO 50
#define TAMANHO_MATRICULA 8
#define BUFSIZE 8192

int par_valido(char c1, char c2) {
    if (isalpha(c1)) {
        if (!isalpha(c2)) return FALSE;
        if (!isupper(c1)) return FALSE;
        if (!isupper(c2)) return FALSE;
    } else {
        if (!isdigit(c1)) return FALSE;
        if (!isdigit(c2)) return FALSE;
    }

    return TRUE;
}

int matricula_valida(char* matricula) {
    int pares_letras=0, pares_num=0;
    if (strlen(matricula) != TAMANHO_MATRICULA) return FALSE;
    if (matricula[2] != '-' || matricula[5] != '-') return FALSE;

    for (int i=0; i<TAMANHO_MATRICULA; i+=3) {
        if (!par_valido(matricula[i], matricula[i+1])) return FALSE;
        if (isalpha(matricula[i])) {
            pares_letras += 1;
        } else {
            pares_num += 1;
        }
    }
    if (pares_letras < 1 || pares_num < 1) return FALSE;
    return TRUE;
    
}

float calcula_custo_horas(int minutos_passados, Parque* parque) {
    int fracoes_15min = 0;
    float custo = 0;
    fracoes_15min = minutos_passados / 15;
    if (minutos_passados%15 != 0) fracoes_15min += 1;

    if (fracoes_15min <= 4) {
        custo += fracoes_15min * (parque->valor_15);
    } else {
        custo += 4 * (parque->valor_15);
        fracoes_15min -= 4;
        custo += fracoes_15min * (parque->valor_15_apos_1hora);
    }
    if (custo >= parque->valor_max_diario) {
        custo = parque->valor_max_diario;
    }
    return custo;
}

float calcula_custo(Registo* registo, Parque* parque) {
    Data* entrada = registo->entrada;
    Data* saida = registo->saida;
    int minutos_passados = 0;
    float custo = 0;
    if (mesmo_dia(entrada, saida)) {
        minutos_passados += (saida->hora - entrada->hora)*60;
        minutos_passados += saida->minutos - entrada->minutos;
        return calcula_custo_horas(minutos_passados, parque);
    } 

    minutos_passados += (24 - entrada->hora)*60;
    minutos_passados += 60 - entrada->minutos; 
    custo += calcula_custo_horas(minutos_passados, parque);
    minutos_passados = 0;
    minutos_passados += (saida->hora)*60;
    minutos_passados += saida->minutos; 
    custo += calcula_custo_horas(minutos_passados, parque);
    custo += conta_dias(entrada, saida) * parque->valor_max_diario;
    
    return custo;
}

void comando_p(char* linha, Lista_Parques lista_parques) {
    char comando;
    char nome[BUFSIZE];
    int capacidade;
    float valor_15;
    float valor_15_apos_1hora;
    float valor_max_diario;
    int argumentos_recebidos;
    int argumentos_esperados = 6;
    Parque* parque;

    argumentos_recebidos = sscanf(linha, "%c \"%[^\"]\" %d %f %f %f", &comando, 
        nome, &capacidade, &valor_15, &valor_15_apos_1hora, &valor_max_diario);
    if (argumentos_recebidos != argumentos_esperados) {

        argumentos_recebidos = sscanf(linha, "%c %s %d %f %f %f", &comando, 
            nome, &capacidade, &valor_15, &valor_15_apos_1hora, &valor_max_diario);
        if (argumentos_recebidos != argumentos_esperados) {

            if (argumentos_recebidos==1) {
                imprime_lista_parques(lista_parques);
                return;
            }
            printf("Erro a ler argumentos do parque.\n");
            return;
        }
    }
    if (procura_parque(lista_parques, nome) != NULL) {
        printf("%s: parking already exists.\n", nome);
        return;
    } 

    if (!verifica_argumentos_parque(capacidade, valor_15, 
        valor_15_apos_1hora, valor_max_diario)) {
        return;
    } 

    if (lista_parques->numero_parques == MAX_PARQUES) {
        printf("too many parks.\n");
        return;
    }
    parque = cria_parque(nome, capacidade, valor_15, valor_15_apos_1hora, valor_max_diario);
    append_Lista_Parques(lista_parques, parque);
}

int le_entrada_ou_saida(char* linha, char* nome_parque, char* matricula, int* dia, int* mes, int* ano, int* hora, int* minutos) {
    char comando;
    int argumentos_recebidos;
    int argumentos_esperados = 8;

    argumentos_recebidos = sscanf(linha, "%c \"%[^\"]\" %s %d-%d-%d %d:%d", &comando, 
        nome_parque, matricula, dia, mes, ano, hora, minutos);
    if (argumentos_recebidos != argumentos_esperados) {

        argumentos_recebidos = sscanf(linha, "%c %s %s %d-%d-%d %d:%d", &comando, 
        nome_parque, matricula, dia, mes, ano, hora, minutos);
        if (argumentos_recebidos != argumentos_esperados) {
            printf("Erro a ler entrada.\n");
            return FALSE;
        }
    }
    return TRUE;
}

void comando_e(char* linha, Lista_Parques lista_parques, HashTable_Carros hashtable_carros, Data* data_sistema) {
    char nome_parque[BUFSIZE];
    char matricula[TAMANHO_ARGUMENTO];
    int dia, mes, ano, hora, minutos;
    Parque* parque;
    Carro* carro;
    Data* data_entrada;
    Registo* registo;

    if (!le_entrada_ou_saida(linha, nome_parque, matricula, &dia, &mes, &ano, &hora, &minutos)) {
        return;
    }
    parque = procura_parque(lista_parques, nome_parque);
    if (parque == NULL) {
        printf("%s: no such parking.\n", nome_parque);
        return;
    } 
    if (parque->lugares_disponiveis == 0) {
        printf("%s: parking is full.\n", nome_parque);
        return;
    }
    if (!matricula_valida(matricula)) {
        printf("%s: invalid licence plate.\n", matricula);
        return;
    }
    data_entrada = cria_data(ano, mes, dia, hora, minutos);
    if (!data_valida(data_entrada)) {
        printf("invalid date.\n");
        free(data_entrada);
        return;
    }
    carro = procurar_hashtable_carros(hashtable_carros, matricula);
    if (carro == NULL) {
        carro = cria_carro(matricula);
        inserir_hashtable_carros(hashtable_carros, carro);
    } else if (carro->dentro_de_parque) {
        printf("%s: invalid vehicle entry.\n", matricula);
        free(data_entrada);
        return;
    }
    if (!data_mais_recente(data_sistema, data_entrada)) {
        printf("invalid date.\n");
        free(data_entrada);
        return;
    }
    
    *data_sistema = *data_entrada;
    registo = criar_registo(parque, carro, data_entrada);
    append_lista_registos(carro->lista_registos, registo);
    parque->lugares_disponiveis -= 1;
    printf("%s %d\n", parque->nome, parque->lugares_disponiveis);
}

void comando_s(char* linha, Lista_Parques lista_parques, HashTable_Carros hashtable_carros, Data* data_sistema) {
    char nome_parque[BUFSIZE];
    char matricula[TAMANHO_ARGUMENTO];
    int dia, mes, ano, hora, minutos;
    float custo;
    Parque* parque;
    Carro* carro;
    Data* data_saida;
    Registo* registo;

    if (!le_entrada_ou_saida(linha, nome_parque, matricula, &dia, &mes, &ano, &hora, &minutos)) {
        return;
    }
    parque = procura_parque(lista_parques, nome_parque);
    if (parque == NULL) {
        printf("%s: no such parking.\n", nome_parque);
        return;
    } 
    if (!matricula_valida(matricula)) {
        printf("%s: invalid licence plate.\n", matricula);
        return;
    }
    data_saida = cria_data(ano, mes, dia, hora, minutos);
    if (!data_valida(data_saida)) {
        printf("invalid date.\n");
        free(data_saida);
        return;
    }
    carro = procurar_hashtable_carros(hashtable_carros, matricula);
    if (carro == NULL) {
        printf("%s: invalid vehicle exit.\n", matricula);
        free(data_saida);
        return;
    } else {
        if (!carro->dentro_de_parque) {
            printf("%s: invalid vehicle exit.\n", matricula);
            free(data_saida);
            return;
        }
        registo = procura_registo_por_parque(carro->lista_registos,parque);
        if (registo == NULL) {
            printf("%s: invalid vehicle exit.\n", matricula);
            free(data_saida);
            return;
        }
    }
    if (!data_mais_recente(data_sistema, data_saida)) {
        printf("invalid date.\n");
        free(data_saida);
        return;
    }
    
    *data_sistema = *data_saida;
    guarda_saida_no_registo(registo, data_saida);
    custo = calcula_custo(registo, parque);
    guarda_custo_no_registo(registo, custo);
    append_lista_registos(parque->lista_saidas, registo);
    parque->lugares_disponiveis += 1;
    imprime_registo(registo);
}



