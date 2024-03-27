#include "ctype.h"
#include "comandos.h"
#include "bool.h"
#include "hashtable_carros.h"

#define MAX_PARQUES 20
#define TAMANHO_ARGUMENTO 50
#define TAMANHO_MATRICULA 9

int matricula_valida(char* matricula) {
    int pares_letras=0, pares_num=0;
    if (strlen(matricula) != TAMANHO_MATRICULA) return FALSE;

    for (int i=0; i<TAMANHO_MATRICULA;i++) {
        if ((i==2 || i==5) && matricula[i]!= '-') return FALSE;

        if (isalpha(matricula[i])) {
            if (islower(matricula[i])) return FALSE;
            if (i==0) continue;
            if(isdigit(matricula[i-1])) return FALSE;
            if (isalpha(matricula[i-1])) pares_letras += 1;
        }
        if (isdigit(matricula[i])) {
            if (i==0) continue;
            if(isalpha(matricula[i-1])) return FALSE;
            if (isdigit(matricula[i-1])) pares_num += 1;
        }
    }
    if (pares_letras > 2 || pares_num > 2) return FALSE;
    return TRUE;
    
}

void comando_p(char* linha, Lista_Parques lista_parques) {
    char comando;
    char nome[TAMANHO_ARGUMENTO];
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

int le_entrada_ou_saida(char* linha, char* nome_parque, char* matricula, char* data, char* hora) {
    char comando;
    int argumentos_recebidos;
    int argumentos_esperados = 5;

    argumentos_recebidos = sscanf(linha, "%c \"%[^\"]\" %s %s %s", &comando, 
        nome_parque, matricula, data, hora);
    if (argumentos_recebidos != argumentos_esperados) {

        argumentos_recebidos = sscanf(linha, "%c %s %s %s %s", &comando, 
        nome_parque, matricula, data, hora);
        if (argumentos_recebidos != argumentos_esperados) {
            printf("Erro a ler entrada.\n");
            return FALSE;
        }
    }
    return TRUE;
}

void comando_e(char* linha, Lista_Parques lista_parques, HashTable_Carros hashtable_carros) {
    char nome_parque[TAMANHO_ARGUMENTO];
    char matricula[TAMANHO_ARGUMENTO];
    char data[TAMANHO_ARGUMENTO];
    char hora[TAMANHO_ARGUMENTO];
    Parque* parque;
    Carro* carro;
    if (!le_entrada_ou_saida(linha, nome_parque, matricula, data, hora)) {
        return;
    }
    parque = procura_parque(lista_parques, nome_parque);
    if (parque == NULL) {
        printf("%s: no such parking.", nome_parque);
        return;
    } 
    if (parque->lugares_disponiveis == 0) {
        printf("%s: parking is full.", nome_parque);
        return;
    }
    if (!matricula_valida(matricula)) {
        printf("%s: invalid licence plate.", matricula);
        return;
    }
    carro = procurar_hashtable_carros(hashtable_carros, matricula);
    if (carro == NULL) {
        carro = cria_carro(matricula);
        inserir_hashtable_carros(hashtable_carros, carro);
    }
}