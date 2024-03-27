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

void libertar_carro(Carro* carro) {
    libertar_lista_registos(carro->lista_registos, /*libertar_registos*/TRUE);
    free(carro->matricula);
    free(carro);
}