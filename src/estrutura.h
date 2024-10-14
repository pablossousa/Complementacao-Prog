#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM_CAIXAS 5

typedef struct Cliente {
    char nome[100];
    char cpf[12];
    int prioridade;  // 1: Alta, 2: Média, 3: Baixa
    int itens;
    struct Cliente *proximo;
} Cliente;

typedef struct Caixa {
    int id;
    bool aberto;  // true: aberto, false: fechado
    Cliente *fila;  // Ponteiro para o primeiro cliente da fila
} Caixa;

void inicializarCaixas(Caixa caixas[NUM_CAIXAS]);
void cadastrarCliente(Caixa caixas[NUM_CAIXAS]);
void atenderCliente(Caixa caixas[NUM_CAIXAS]);
void abrirOuFecharCaixa(Caixa caixas[NUM_CAIXAS]);
void imprimirClientesEmEspera(Caixa caixas[NUM_CAIXAS]);
void imprimirStatusCaixas(Caixa caixas[NUM_CAIXAS]);

#endif
