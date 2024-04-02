/**
 * Define a função que recebe o input e o que cada comando faz.
 * 
 * @file comandos.c
 * @author ist1109247
*/
#include <stdio.h> 
#include <stdlib.h>
#include "comandos.h"
#include "ler_input.h"
#include "bool.h"
#include "verifica_argumentos.h"

/**
 * @brief Recebe uma linha de input e redireciona para o comando certo.
 */
void recebe_input_identifica_comando(Lista_Parques lista_parques, 
                                     HashTable_Carros hashtable_carros, 
                                     Data* data_sistema) {
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

/**
 * @brief Analisa uma linha de input. Se for apenas "p", lista os parques 
 * existentes. Senão, cria um parque de estacionamento com o nome e 
 * regime de facturação fornecidos no input.
 */
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

    if (!verifica_argumentos_p(lista_parques, nome_parque, capacidade, valor_15,
                               valor_15_apos_1hora, valor_max_diario)) {
        return;
    }
    
    parque = cria_parque(nome_parque, capacidade, valor_15, 
                         valor_15_apos_1hora, valor_max_diario);
    insere_parque_no_fim(lista_parques, parque);
}

/**
 * @brief Executa a entrada de um carro num parque. Cria um registo 
 * correspondente à entrada, atualiza as listas de registos e o número de 
 * lugares disponíveis do parque.
 */
void executa_entrada(Parque* parque, Carro* carro, Data* data_entrada, 
                     Data* data_sistema) {
    Registo* registo;

    *data_sistema = *data_entrada;
    registo = cria_registo(parque, carro, data_entrada);
    insere_registo_por_nome_parque(carro->lista_registos, registo);
    insere_registo_no_fim(parque->lista_entradas, registo);
    parque->lugares_disponiveis -= 1;
    carro->dentro_de_parque = TRUE;
}

/**
 * @brief Analisa uma linha de input, que deve ter o nome de um parque, uma
 * matricula e uma data de entrada. Regista a entrada do veículo. Imprime o 
 * nome do parque, a capacidade e os lugares disponíveis.
 */
void comando_e(char* linha, Lista_Parques lista_parques, 
               HashTable_Carros hashtable_carros, Data* data_sistema) {
    char nome_parque[BUFSIZE], matricula[TAMANHO_MATRICULA];
    int dia, mes, ano, hora, minutos;
    Parque* parque;
    Data* data_entrada;
    Carro* carro;

    if (!le_e_s(linha, nome_parque, matricula, &dia, 
                &mes, &ano, &hora, &minutos)) {
        return;
    }

    parque = procura_parque(lista_parques, nome_parque);
    data_entrada = cria_data(ano, mes, dia, hora, minutos);
    carro = procura_carro_na_hashtable(hashtable_carros, matricula);
    if (!verifica_argumentos_e(parque, nome_parque, hashtable_carros, 
        &carro, matricula, data_entrada, data_sistema)) {
        free(data_entrada);
        return;
    }

    executa_entrada(parque, carro, data_entrada, data_sistema);
    printf("%s %d\n", parque->nome, parque->lugares_disponiveis);
}

/**
 * @brief Executa a saída de um carro de um parque. Guarda a data de saída e 
 * custo no registo correspondente ao estacionamento do carro. Adiciona o 
 * registo à lista de saídas do parque e muda o número de lugares disponíveis.
 */
void executa_saida(Parque* parque, Carro* carro, Registo* registo, 
                   Data* data_saida, Data* data_sistema) {
    float custo;
    *data_sistema = *data_saida;
    guarda_saida_no_registo(registo, data_saida);
    custo = calcula_custo(registo, parque);
    guarda_custo_no_registo(registo, custo);
    insere_registo_no_fim(parque->lista_saidas, registo);
    parque->lugares_disponiveis += 1;
    carro->dentro_de_parque = FALSE;
}

/**
 * @brief Analisa uma linha de input, que deve ter o nome de um parque, uma 
 * matrícula e uma data de saída. Regista a saída do carro. Imprime a 
 * matrícula, data de entrada, data de saída e custo do estacionamento.
 */
void comando_s(char* linha, Lista_Parques lista_parques, 
               HashTable_Carros hashtable_carros, Data* data_sistema) {
    char nome_parque[BUFSIZE], matricula[TAMANHO_MATRICULA];
    int dia, mes, ano, hora, minutos;
    Parque* parque;
    Carro* carro;
    Data* data_saida;
    Registo* registo;

    if (!le_e_s(linha, nome_parque, matricula, &dia, 
                &mes, &ano, &hora, &minutos)) {
        return;
    }

    parque = procura_parque(lista_parques, nome_parque);
    data_saida = cria_data(ano, mes, dia, hora, minutos);
    carro = procura_carro_na_hashtable(hashtable_carros, matricula);
    if (!verifica_argumentos_s(parque, nome_parque, &carro, matricula, 
                               &registo, data_saida, data_sistema)){
        free(data_saida);
        return;
    }
    
    executa_saida(parque, carro, registo, data_saida, data_sistema);
    imprime_saida(registo);
}

/**
 * @brief Analisa uma linha de input, que deve ter a matrícula de um carro. 
 * Lista todas as entradas e saídas do carro.
 */
void comando_v(char* linha, HashTable_Carros hashtable_carros) {
    char matricula[TAMANHO_MATRICULA];
    Carro* carro;

    if(!le_v(linha, matricula)) {
        return;
    }

    carro = procura_carro_na_hashtable(hashtable_carros, matricula);
    if (!verifica_argumentos_v(carro, matricula)) {
        return;
    }

    itera_lista_registos(carro->lista_registos, imprime_entrada_saida);
}

/**
 * @brief Analisa o input, que deve ter o nome de um parque e, possivelmente, 
 * uma data. Se tiver uma data, imprime as matrículas dos carros 
 * que estiveram no parque nesse dia, a hora de saída e a faturação. Se não   
 * tiver uma data, imprime a faturação do parque a cada dia.
 */
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
    if (!verifica_parque_existe(parque, nome_parque)) {
        return;
    }

    if (argumentos_recebidos == ARGS_F_SEM_DATA) {
        imprime_faturacao_todos_dias(parque->lista_saidas);
        return;
    }

    data = cria_data(ano, mes, dia, 0, 0);
    if (!verifica_data_f(data, data_sistema)) {
        free(data);
        return;
    }

    registo_node_data = procura_primeiro_registo_node_do_dia
                        (parque->lista_saidas, data);
    imprime_faturacao_num_dia(registo_node_data, data);
    free(data);
    
}   

/**
 * @brief Analisa uma linha de input, que deve ter o nome de um parque. Remove 
 * o parque e todos os registos de entradas e saídas nesse parque. Imprime os 
 * nomes dos parques restantes.
 */
void comando_r(char* linha, Lista_Parques lista_parques) {
    char nome_parque[BUFSIZE];
    Parque* parque;

    if(!le_r(linha, nome_parque)) {
        return;
    }
    parque = procura_parque(lista_parques, nome_parque);
    if (!verifica_parque_existe(parque, nome_parque)) {
        return;
    }
    remove_parque(lista_parques, parque);
    imprime_lista_parques_por_nome(lista_parques);
}

/**
 * @brief Imprime todos os parques, o seu regime de 
 * faturação e os seus registos. Imprime todos os carros, o seu estado e os 
 * seus registos. Serve para ver de forma clara o que acontece entre comandos.
 */
void comando_t(Lista_Parques lista_parques, HashTable_Carros hashtable_carros) {
    itera_lista_parques(lista_parques, imprime_parque_tudo);
    imprime_hashtable_carros(hashtable_carros);
}
