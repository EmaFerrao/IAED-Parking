#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "carro.h"
#include "bool.h"

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

    for (int i = 0; i < TAMANHO_MATRICULA; i += 3) {
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

Carro* cria_carro(char* matricula) {
    Carro* carro = (Carro*) malloc(sizeof(Carro));
    carro->matricula = strdup(matricula);
    carro->dentro_de_parque = TRUE;
    carro->lista_registos = cria_lista_registos();
    return carro;
}

void imprime_carro_tudo(Carro* carro) {
    printf("%s\n", carro->matricula);
    if (carro->dentro_de_parque) {
        printf("Dentro de parque\n");
    } else {
        printf("Fora de parque\n");
    }
    printf("REGISTOS:\n");
    itera_lista_registos(carro->lista_registos, imprime_registo);
    printf("\n");
}

void libertar_carro(Carro* carro) {
    libertar_lista_registos(carro->lista_registos, FALSE /*registos são libertados no parque*/);
    free(carro->matricula);
    free(carro);
}