#include <stdio.h>
#include <stdlib.h>
#include "filaEnc.h"

void inicializa(FilaEnc *f) {
    f->frente = NULL;
    f->final = NULL;
}

int estaVazia(FilaEnc *f) {
    return f->frente == NULL;
}

int enfileira(FilaEnc *f, Produto valor) {
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo == NULL)
        return 0;

    novo->dado = valor;
    novo->prox = NULL;

    if (f->final != NULL)
        f->final->prox = novo; // o antigo final passa a apontar para o novo nodo
    else
        f->frente = novo;      // fila estava vazia: novo nodo também é a frente

    f->final = novo;
    return 1;
}

int desenfileira(FilaEnc *f, Produto *valorRemovido) {
    Nodo *removido;

    if (estaVazia(f)) // underflow
        return 0;

    removido = f->frente;
    *valorRemovido = removido->dado;
    f->frente = removido->prox;

    if (f->frente == NULL) // a fila ficou vazia
        f->final = NULL;

    free(removido);
    return 1;
}

int tamanho(FilaEnc *f) {
    Nodo *aux = f->frente;
    int contador = 0;

    while (aux != NULL) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}

// B3
void removerDaFilaPorCod(FilaEnc *fila, int cod) {

    FilaEnc filaTemp;
    inicializa(&filaTemp);

    Produto prodTemp;

    int prodRemovido = 0;

    while (!estaVazia(fila)) {

        desenfileira(fila, &prodTemp);

        if (prodTemp.cod == cod && !prodRemovido) {
            prodRemovido = 1;
            continue;
        }

        enfileira(&filaTemp, prodTemp);
    }

    while(!estaVazia(&filaTemp)) {
        desenfileira(&filaTemp, &prodTemp);
        enfileira(fila, prodTemp);
    }
}

// B5
void separarParImpar(FilaEnc *fila, FilaEnc *pares, FilaEnc *impares) {

    Produto prodTemp;

    inicializa(pares);
    inicializa(impares);

    while (!estaVazia(fila)) {
        desenfileira(fila, &prodTemp);

        if (prodTemp.cod % 2 == 0) {
            enfileira(pares, prodTemp);
        }
        else {
            enfileira(impares, prodTemp);
        }
    }
}

// B6
float somarPrecosImparesPreservando(FilaEnc *fila) {

    // desenfileira todos os itens fazendo as somas necessarias
    // enfileira numa fila temporaria

    FilaEnc filaTemp;
    inicializa(&filaTemp);

    Produto prodTemp;

    float somaPrecos = 0.0f;

    while (!estaVazia(fila)) {
        desenfileira(fila, &prodTemp);

        if (prodTemp.cod % 2 != 0) somaPrecos += prodTemp.preco;

        enfileira(&filaTemp, prodTemp);
    }
 
    // enfileira de volta para a fila original
    while (!estaVazia(&filaTemp))
    {
        desenfileira(&filaTemp, &prodTemp);
        enfileira(fila, prodTemp);
    }
    
    return somaPrecos;
}

// B7
int temConsecutivosIguais(FilaEnc *fila) {
    FilaEnc filaTemp;
    inicializa(&filaTemp);

    Produto prodAtual, prodAnterior;
    desenfileira(fila, &prodAnterior);

    int temConsecIguais = 0;

    while (!estaVazia(fila)) {
        desenfileira(fila, &prodAtual);

        if (prodAtual.cod == prodAnterior.cod) temConsecIguais = 1;
        prodAnterior = prodAtual;

        enfileira(&filaTemp, prodAtual);
    }

    while (!estaVazia(&filaTemp))
    {
        desenfileira(&filaTemp, &prodAtual);
        enfileira(fila, prodAtual);
    }
    
    return temConsecIguais;
}

