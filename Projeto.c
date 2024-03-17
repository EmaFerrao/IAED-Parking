/* iaed24 - ist1109247 - project */
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#define FALSE 0
#define TRUE 1

typedef struct {
    char *nome;
    int capacidade;
    float valor_15;
    float valor_15_apos_1hora;
    float valor_max_diario;
    float faturacao;
} Parque; 

void ler_input(){
    char c;
    while ((c=getchar() != 'q')){
        switch (c) {
            case 'p':
                le_parque();
        }
    }
}

int le_nome_parque(){
    char buffer[256];
    if (scanf("%s", buffer)){
        char *nome_parque;
        nome_parque = (char*) malloc(sizeof(char)*strlen(buffer));
        strcpy(nome_parque, buffer);
    }
    else{
        return FALSE;
    }
    
}



void le_parque(){
    int args;
    args = le_nome_parque();
    if (args == TRUE){
        procura_parque();
        int capacidade;
        float valor_15;
        float valor_15_apos_1hora;
        float valor_max_diario;
        float faturacao;

        scanf("%d", &capacidade);
        scanf("%f", &valor_15);
        scanf("%f", &valor_15_apos_1hora);
        scanf("%f", &valor_max_diario);
        scanf("%f", &faturacao);
    }

    

}

int main(){
    return 0;
}