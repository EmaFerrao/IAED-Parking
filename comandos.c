#include <stdio.h> 
#include <stdlib.h>

#include "comandos.h"
#include "ler_input.h"
#include "bool.h"

void recebe_input_identifica_comando(Lista_Parques lista_parques, HashTable_Carros hashtable_carros, Data* data_sistema) {
    char linha[BUFSIZE];

    do {
        fgets(linha, sizeof(linha), stdin);
        switch (linha[0]){
            case 'p':
                comando_p(linha, lista_parques);
                break;
            case 'e':
                comando_e(linha, lista_parques, hashtable_carros, data_sistema);
                break;
            case 's':
                comando_s(linha, lista_parques, hashtable_carros, data_sistema);
                break;
            case 'v':
                comando_v(linha, hashtable_carros);
                break;
            case 'f':
                comando_f(linha, lista_parques, data_sistema);
                break;
            case 'r':
                comando_r(linha, lista_parques);
                break;
            case 't':
                comando_t(lista_parques, hashtable_carros);
                break;
        }
    } while (linha[0] != 'q');
}

void comando_p(char* linha, Lista_Parques lista_parques) {
    char nome_parque[BUFSIZE];
    int capacidade, argumentos_recebidos, argumentos_so_p = 1;
    float valor_15, valor_15_apos_1hora, valor_max_diario;
    Parque* parque;

    argumentos_recebidos = le_p(linha, nome_parque, &capacidade, &valor_15, 
        &valor_15_apos_1hora, &valor_max_diario);
    if (!argumentos_recebidos) {
        return;
    }
    if (argumentos_recebidos == argumentos_so_p) {
        imprime_lista_parques(lista_parques);
        return;
    }

    if (procura_parque(lista_parques, nome_parque) != NULL) {
        printf("%s: parking already exists.\n", nome_parque);
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
    parque = cria_parque(nome_parque, capacidade, valor_15, valor_15_apos_1hora, valor_max_diario);
    insere_parque_no_fim(lista_parques, parque);
}

int parque_existe_matricula_valida_data_valida(Parque* parque, char* nome_parque, char* matricula, Data* data) {
    if (parque == NULL) {
        printf("%s: no such parking.\n", nome_parque);
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

int data_mais_recente_que_sistema(Data* data, Data* data_sistema) {
    if (!data_mais_recente(data_sistema, data)) {
        printf("invalid date.\n");
        return FALSE;
    }
    return TRUE;
}

int verifica_argumentos_entrada(Parque* parque, char* nome_parque, 
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
    if (!data_mais_recente_que_sistema(data_entrada, data_sistema)) {
        return FALSE;
    }

    return TRUE;
}

void executa_entrada(Parque* parque, Carro* carro, Data* data_entrada, Data* data_sistema) {
    Registo* registo;

    *data_sistema = *data_entrada;
    registo = criar_registo(parque, carro, data_entrada);
    insere_registo_por_nome_parque(carro->lista_registos, registo);
    insere_registo_no_fim(parque->lista_entradas, registo);
    parque->lugares_disponiveis -= 1;
    carro->dentro_de_parque = TRUE;
}

void comando_e(char* linha, Lista_Parques lista_parques, HashTable_Carros hashtable_carros, Data* data_sistema) {
    char nome_parque[BUFSIZE], matricula[TAMANHO_MATRICULA];
    int dia, mes, ano, hora, minutos;
    Parque* parque;
    Data* data_entrada;
    Carro* carro;

    if (!le_e_s(linha, nome_parque, matricula, &dia, &mes, &ano, &hora, &minutos)) {
        return;
    }

    parque = procura_parque(lista_parques, nome_parque);
    data_entrada = cria_data(ano, mes, dia, hora, minutos);
    carro = procurar_hashtable_carros(hashtable_carros, matricula);

    if (!verifica_argumentos_entrada(parque, nome_parque, hashtable_carros, 
        &carro, matricula, data_entrada, data_sistema)) {
        free(data_entrada);
        return;
    }

    executa_entrada(parque, carro, data_entrada, data_sistema);
    printf("%s %d\n", parque->nome, parque->lugares_disponiveis);
}

int verifica_argumentos_saida(Parque* parque, char* nome_parque, Carro** carro,
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
    if (!data_mais_recente_que_sistema(data_saida, data_sistema)) {
        return FALSE;
    }

    return TRUE;
}

void executa_saida(Parque* parque, Carro* carro, Registo* registo, Data* data_saida, Data* data_sistema) {
    float custo;

    *data_sistema = *data_saida;
    guarda_saida_no_registo(registo, data_saida);
    custo = calcula_custo(registo, parque);
    guarda_custo_no_registo(registo, custo);
    insere_registo_no_fim(parque->lista_saidas, registo);
    parque->lugares_disponiveis += 1;
    carro->dentro_de_parque = FALSE;
}

void comando_s(char* linha, Lista_Parques lista_parques, HashTable_Carros hashtable_carros, Data* data_sistema) {
    char nome_parque[BUFSIZE], matricula[TAMANHO_MATRICULA];
    int dia, mes, ano, hora, minutos;
    Parque* parque;
    Carro* carro;
    Data* data_saida;
    Registo* registo;

    if (!le_e_s(linha, nome_parque, matricula, &dia, &mes, &ano, &hora, &minutos)) {
        return;
    }

    parque = procura_parque(lista_parques, nome_parque);
    data_saida = cria_data(ano, mes, dia, hora, minutos);
    carro = procurar_hashtable_carros(hashtable_carros, matricula);
    if (!verifica_argumentos_saida(parque, nome_parque, &carro, 
        matricula, &registo, data_saida, data_sistema)) {
        free(data_saida);
        return;
    }
    
    executa_saida(parque, carro, registo, data_saida, data_sistema);
    imprime_saida(registo);
}

void comando_v(char* linha, HashTable_Carros hashtable_carros) {
    char matricula[TAMANHO_MATRICULA];
    Carro* carro;

    if(!le_v(linha, matricula)) {
        return;
    }

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

void comando_f(char* linha, Lista_Parques lista_parques, Data* data_sistema) {
    char nome_parque[BUFSIZE];
    int ano = 0, mes = 0, dia = 0;
    int argumentos_recebidos;
    Parque* parque;
    Data* data;
    Registo_Node* registo_node_data;

    argumentos_recebidos = le_f(linha, nome_parque, &dia, &mes, &ano);
    if (argumentos_recebidos != ARGS_F_COM_DATA && 
        argumentos_recebidos != ARGS_F_SEM_DATA) {
        return;
    }

    parque = procura_parque(lista_parques, nome_parque);
    if (parque == NULL) {
        printf("%s: no such parking.\n", nome_parque);
        return;
    }

    if (argumentos_recebidos == ARGS_F_SEM_DATA) {
        imprime_faturacao(parque->lista_saidas);
        return;
    }

    data = cria_data(ano, mes, dia, 0, 0);
    if (!data_valida(data) || data_mais_recente(data_sistema, data)) {
        printf("invalid date.\n");
    } else {
        registo_node_data = procura_primeiro_registo_node_do_dia(parque->lista_saidas, data);
        imprime_faturacao_num_dia(registo_node_data, data);
    }
    
    free(data);
}   

void comando_r(char* linha, Lista_Parques lista_parques) {
    char nome_parque[BUFSIZE];
    Parque* parque;

    if(!le_r(linha, nome_parque)) {
        return;
    }
    parque = procura_parque(lista_parques, nome_parque);
    if (parque == NULL) {
        printf("%s: no such parking.\n", nome_parque);
        return;
    } 
    remove_parque(lista_parques, parque);
    imprime_lista_parques_por_nome(lista_parques);
}

void comando_t(Lista_Parques lista_parques, HashTable_Carros hashtable_carros) {
    itera_lista_parques(lista_parques, imprime_parque_tudo);
    imprime_hashtable_carros(hashtable_carros);
}

