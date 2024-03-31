#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "carro.h"
#include "bool.h"


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
    libertar_lista_registos(carro->lista_registos, /*libertar_registos*/FALSE);
    free(carro->matricula);
    free(carro);
}