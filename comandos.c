#include "ctype.h"
#include "comandos.h"
#include "bool.h"
#include "hashtable_carros.h"

#define MAX_PARQUES 20
#define TAMANHO_ARGUMENTO 50
#define TAMANHO_MATRICULA 8

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
    char nome_parque[TAMANHO_ARGUMENTO];
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
    carro = procurar_hashtable_carros(hashtable_carros, matricula);
    if (carro == NULL) {
        carro = cria_carro(matricula);
        inserir_hashtable_carros(hashtable_carros, carro);
    } else if (carro->dentro_de_parque) {
        printf("%s: invalid vehicle entry.\n", matricula);
        return;
    }
    
    data_entrada = cria_data(ano, mes, dia, hora, minutos);
    if (!verifica_data(data_sistema, data_entrada)) {
        printf("invalid date.\n");
        return;
    }
    data_sistema = data_entrada;
    registo = criar_registo(parque, carro, data_entrada);
    append_lista_registos(carro->lista_registos, registo);
}