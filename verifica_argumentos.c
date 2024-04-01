#include <stdio.h>
#include "verifica_argumentos.h"

int verifica_capacidade_valores(int capacidade, float valor_15, float valor_15_apos_1hora, float valor_max_diario) {

    if (capacidade <= 0) {
        printf("%d: invalid capacity.\n", capacidade);
        return FALSE;
    }
    if (valor_15 <= 0 || valor_15_apos_1hora <= 0 || valor_max_diario <= 0) {
        printf("invalid cost.\n");
        return FALSE;
    }
    if (!(valor_15 < valor_15_apos_1hora && valor_15_apos_1hora < valor_max_diario)) {
        printf("invalid cost.\n");
        return FALSE;
    }

    return TRUE;
}

int verifica_argumentos_p(Lista_Parques lista_parques, char* nome_parque, int capacidade, float valor_15, float valor_15_apos_1hora, float valor_max_diario) {

    if (procura_parque(lista_parques, nome_parque) != NULL) {
        printf("%s: parking already exists.\n", nome_parque);
        return FALSE;
    } 
    if (!verifica_capacidade_valores(capacidade, valor_15, 
        valor_15_apos_1hora, valor_max_diario)) {
        return FALSE;
    } 
    if (lista_parques->numero_parques == MAX_PARQUES) {
        printf("too many parks.\n");
        return FALSE;
    }

    return TRUE;
}

int verifica_parque_existe(Parque* parque, char* nome_parque) {
    if (parque == NULL) {
        printf("%s: no such parking.\n", nome_parque);
        return FALSE;
    } 

    return TRUE;
}

int parque_existe_matricula_valida_data_valida(Parque* parque, 
char* nome_parque, char* matricula, Data* data) {

    if (!verifica_parque_existe(parque, nome_parque)) {
        return FALSE;
    }
    if (!matricula_valida(matricula)) {
        printf("%s: invalid licence plate.\n", matricula);
        return FALSE;
    }
    if (!data_valida(data)) {
        printf("invalid date.\n");
        return FALSE;
    }
    return TRUE;
}

int verifica_argumentos_e(Parque* parque, char* nome_parque, 
HashTable_Carros hashtable_carros, Carro** carro, char* matricula, 
Data* data_entrada, Data* data_sistema) {

    if (!parque_existe_matricula_valida_data_valida(parque, nome_parque, matricula, data_entrada)) {
        return FALSE;
    }
    if (parque->lugares_disponiveis == 0) {
        printf("%s: parking is full.\n", nome_parque);
        return FALSE;
    }
    if (*carro == NULL) {
        *carro = cria_carro(matricula);
        inserir_hashtable_carros(hashtable_carros, *carro);
    } else if ((*carro)->dentro_de_parque) {
        printf("%s: invalid vehicle entry.\n", matricula);
        return FALSE;
    }
    if (!data_mais_recente(data_sistema, data_entrada)) {
        printf("invalid date.\n");
        return FALSE;
    }

    return TRUE;
}

int verifica_argumentos_s(Parque* parque, char* nome_parque, Carro** carro,
char* matricula, Registo** registo, Data* data_saida, Data* data_sistema) {

    if (!parque_existe_matricula_valida_data_valida(parque, nome_parque, matricula, data_saida)) {
        return FALSE;
    }
    if (*carro == NULL) {
        printf("%s: invalid vehicle exit.\n", matricula);
        return FALSE;
    } 
    if (!(*carro)->dentro_de_parque) {
        printf("%s: invalid vehicle exit.\n", matricula);
        return FALSE;
    }
    (*registo) = procura_registo_sem_saida_no_parque((*carro)->lista_registos,parque);
    if (registo == NULL) {
        printf("%s: invalid vehicle exit.\n", matricula);
        return FALSE;
    }
    if (!data_mais_recente(data_sistema, data_saida)) {
        printf("invalid date.\n");
        return FALSE;
    }

    return TRUE;
}

int verifica_argumentos_v(Carro* carro, char* matricula) {
    if (!matricula_valida(matricula)) {
        printf("%s: invalid licence plate.\n", matricula);
        return FALSE;
    }
    if (carro == NULL || carro->lista_registos->head == NULL) {
        printf("%s: no entries found in any parking.\n", matricula);
        return FALSE;
    }

    return TRUE;
}

int verifica_argumentos_f(Data* data, Data* data_sistema) {
    if (!data_valida(data) || data_mais_recente(data_sistema, data)) {
        printf("invalid date.\n");
        return FALSE;
    }

    return TRUE;
}

