/**
 * Define os métodos de um carro.
 * 
 * @file carro.c
 * @author ist1109247
*/
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "carro.h"
#include "bool.h"

/**
 * @brief Verifica se dois caracteres são do mesmo tipo (letra ou dígito). 
 * Se forem letras, verifica se são maiúsculas.
 */
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

/**
 * @brief Verifica se matrícula é válida
 */
int matricula_valida(char* matricula) {
    int pares_letras=0, pares_num=0;
    if (strlen(matricula) != TAMANHO_MATRICULA-1) return FALSE;
    if (matricula[INDICE_PRIMEIRO_HIFEN] != '-' || 
        matricula[INDICE_SEGUNDO_HIFEN] != '-') return FALSE;

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

/**
 * @brief Cria e devolve um novo carro, com dentro de parque TRUE. 
 * Quando carro deixar de ser utilizado, tem de ser libertado.
 */
Carro* cria_carro(char* matricula) {
    Carro* carro = (Carro*) malloc(sizeof(Carro));
    carro->matricula = strdup(matricula);
    carro->dentro_de_parque = TRUE;
    carro->lista_registos = cria_lista_registos();
    return carro;
}

/**
 * @brief Imprime matrícula do carro, se está dentro ou fora de um parque e
 * todos os seus registos. 
 */
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

/**
 * @brief Liberta o carro, a matrícula e a sua 
 * lista de registos, sem libertar os registos.
 */
void liberta_carro(Carro* carro) {
    // registos são libertados no parque
    liberta_lista_registos(carro->lista_registos, FALSE);
    free(carro->matricula);
    free(carro);
}
