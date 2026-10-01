#ifndef FILA_ARV_H
#define FILA_ARV_H

/* Adaptacao do TAD FilaEnc (Aula 9b) para armazenar NodoArv*.
   A fila guarda ENDERECOS de nos da arvore, nao copias dos nos.
   Necessaria para o caminhamento em nivel (BFS). */

typedef struct str_NodoArv NodoArv;   /* forward declaration */

typedef struct str_NodoFila {
    NodoArv             *dado;        /* endereco do no da arvore */
    struct str_NodoFila *prox;
} NodoFila;

typedef struct {
    NodoFila *frente;
    NodoFila *final;
} FilaArv;

void     inicializaArv (FilaArv *f);
int      estaVaziaArv  (const FilaArv *f);
void     enqueueArv    (FilaArv *f, NodoArv *no);
NodoArv* dequeueArv    (FilaArv *f);   /* retorna o ponteiro diretamente */

#endif
