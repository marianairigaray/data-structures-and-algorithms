#include <stdlib.h>
#include "filaArv.h"

void inicializaArv(FilaArv *f) {
    f->frente = NULL;
    f->final  = NULL;
}

int estaVaziaArv(const FilaArv *f) {
    return f->frente == NULL;
}

void enqueueArv(FilaArv *f, NodoArv *no) {
    NodoFila *novo = (NodoFila*) malloc(sizeof(NodoFila));
    novo->dado = no;
    novo->prox = NULL;
    if (f->final == NULL) {
        f->frente = novo;
        f->final  = novo;
    } else {
        f->final->prox = novo;
        f->final       = novo;
    }
}

NodoArv* dequeueArv(FilaArv *f) {
    NodoFila *rem;
    NodoArv  *val;
    if (estaVaziaArv(f)) return NULL;
    rem       = f->frente;
    val       = rem->dado;
    f->frente = rem->prox;
    if (f->frente == NULL)
        f->final = NULL;   /* fila ficou vazia: zera final tambem */
    free(rem);
    return val;
}
