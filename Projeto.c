// ist1109247
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>

typedef struct {
    char *nome;
    int capacidade;
    float valor_15;
    float valor_15_apos_1hora;
    float valor_max_diario;
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

void le_parque(){
    char c;
    c = getchar();

    if (c == '\n'){
        // lista parques existentes
    }
    else{
        Parque parque;

        while ((c=getchar()) != '\n'){
            scanf("%s%d%f%f%f", parque)
        }
    }

}

int main(){
    return 0;
}