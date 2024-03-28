#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "comandos.h"
#include "bool.h"
#include "hashtable_carros.h"

#define MAX_PARQUES 20
#define TAMANHO_ARGUMENTO 50
#define TAMANHO_MATRICULA 9
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
    if (strlen(matricula) != TAMANHO_MATRICULA-1) return FALSE;
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

float calcula_custo(Registo* registo, Parque* parque) {
    int minutos, dias, minutos_por_dia = 24*60;
    float custo_dias = 0, custo = 0;

    minutos = diferenca_em_minutos(registo->entrada, registo->saida);
    dias = minutos / minutos_por_dia;
    custo_dias += dias * parque->valor_max_diario;
    minutos = minutos % minutos_por_dia;
    if (minutos <= 60) {
        custo += (minutos / 15) * parque->valor_15;
        if (minutos % 15 != 0) custo += parque->valor_15;
    } else {
        custo += 4 * parque->valor_15;
        minutos -= 60;
        custo += (minutos / 15) * parque->valor_15_apos_1hora;
        if (minutos % 15 != 0) custo += parque->valor_15_apos_1hora;
    }
    if (custo > parque->valor_max_diario) custo = parque->valor_max_diario;
    
    return custo_dias + custo;
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
    char matricula[TAMANHO_MATRICULA];
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
    insere_lista_registos_alfabeto(carro->lista_registos, registo);
    parque->lugares_disponiveis -= 1;
    carro->dentro_de_parque = TRUE;
    printf("%s %d\n", parque->nome, parque->lugares_disponiveis);
}

void comando_s(char* linha, Lista_Parques lista_parques, HashTable_Carros hashtable_carros, Data* data_sistema) {
    char nome_parque[BUFSIZE];
    char matricula[TAMANHO_MATRICULA];
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
    carro->dentro_de_parque = FALSE;
    imprime_saida(registo);
}

void comando_v(char* linha, HashTable_Carros hashtable_carros) {
    char matricula[TAMANHO_MATRICULA];
    char comando;
    Carro* carro;

    sscanf(linha, "%c %s", &comando, matricula);
    if (!matricula_valida(matricula)) {
        printf("%s: invalid licence plate.\n", matricula);
        return;
    }
    carro = procurar_hashtable_carros(hashtable_carros, matricula);
    if (carro == NULL || carro->lista_registos->head == NULL) {
        printf("%s: no entries found in any parking.\n", matricula);
        return;
    }
    itera_lista_registos(carro->lista_registos, imprime_entrada_saida);
}

void comando_f(char* linha, Lista_Parques lista_parques) {
    char nome_parque[BUFSIZE];
    char comando;
    int ano=0, mes=0, dia=0;
    int argumentos_recebidos;
    Parque* parque;
    Data* data;
    Registo_Node* registo_node_data;

    argumentos_recebidos = sscanf(linha, "%c %s %d-%d-%d", &comando, nome_parque, &dia, &mes, &ano);
    if (argumentos_recebidos != 5 && argumentos_recebidos != 2) {
        return;
    }

    parque = procura_parque(lista_parques, nome_parque);
    if (parque == NULL) {
        printf("%s: no such parking.\n", nome_parque);
        return;
    }
    if (argumentos_recebidos == 2) {
        imprime_faturacao(parque->lista_saidas);
        return;
    }
    data = cria_data(ano, mes, dia, 0, 0);
    if (!data_valida(data)) {
        printf("invalid date.\n");
        return;
    }
    registo_node_data = procura_registo_por_dia(parque->lista_saidas, data);
    imprime_faturacao_num_dia(registo_node_data, data);
}   


