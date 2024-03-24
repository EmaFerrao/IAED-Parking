#ifndef REGISTO_H
#define REGISTO_H

typedef struct Parque Parque;
typedef struct Carro Carro;

typedef struct {
    Parque* parque;
    Carro* carro;
    char* data_entrada;
    char* hora_entrada;
    char* data_saida;
    char* hora_saida;
    int custo;
} Registo;

typedef void (*Operacao_Registo)(Registo*);

void libertar_registo(Registo* registo);

#endif
