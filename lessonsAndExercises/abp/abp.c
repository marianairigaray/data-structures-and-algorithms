#include <stdio.h>
#include <stdlib.h>
#include "abp.h"
#include "filaArv.h"

/* ================================================================
   TAD AbpProduto
================================================================ */

NodoArv* abpCriar(void) {
    return NULL;
}

NodoArv* abpBuscar(NodoArv *raiz, int cod) {
    if (raiz == NULL)          return NULL;   /* nao encontrado */
    if (cod == raiz->dado.cod) return raiz;   /* encontrado     */
    if (cod < raiz->dado.cod)
        return abpBuscar(raiz->esq, cod);
    else
        return abpBuscar(raiz->dir, cod);
}

NodoArv* abpInserir(NodoArv *raiz, Produto valor) {
    if (raiz == NULL) {                        /* achou o lugar */
        NodoArv *novo = (NodoArv*) malloc(sizeof(NodoArv));
        novo->dado = valor;
        novo->esq  = NULL;
        novo->dir  = NULL;
        return novo;
    }
    if (valor.cod < raiz->dado.cod)
        raiz->esq = abpInserir(raiz->esq, valor);
    else if (valor.cod > raiz->dado.cod)
        raiz->dir = abpInserir(raiz->dir, valor);
    /* cod duplicado: nao insere */
    return raiz;
}

/* auxiliar: menor no da subarvore (mais a esquerda possivel) */
static NodoArv* abpMinimo(NodoArv *raiz) {
    if (raiz == NULL) return NULL;
    while (raiz->esq != NULL)
        raiz = raiz->esq;
    return raiz;
}

NodoArv* abpRemover(NodoArv *raiz, int cod) {
    NodoArv *filho, *sucessor;
    if (raiz == NULL) return NULL;   /* nao encontrado */

    if (cod < raiz->dado.cod) {
        raiz->esq = abpRemover(raiz->esq, cod);
    } else if (cod > raiz->dado.cod) {
        raiz->dir = abpRemover(raiz->dir, cod);
    } else {
        /* achou o no a remover */
        if (raiz->esq == NULL && raiz->dir == NULL) {
            /* caso 1: folha */
            free(raiz);
            return NULL;
        } else if (raiz->esq == NULL) {
            /* caso 2: so filho direito — ele sobe */
            filho = raiz->dir;
            free(raiz);
            return filho;
        } else if (raiz->dir == NULL) {
            /* caso 2: so filho esquerdo — ele sobe */
            filho = raiz->esq;
            free(raiz);
            return filho;
        } else {
            /* caso 3: dois filhos — substitui pelo sucessor em-ordem
               (minimo da subarvore direita; nunca tem filho esquerdo) */
            sucessor   = abpMinimo(raiz->dir);
            raiz->dado = sucessor->dado;
            raiz->dir  = abpRemover(raiz->dir, sucessor->dado.cod);
        }
    }
    return raiz;
}

void abpDestruir(NodoArv *raiz) {
    if (raiz == NULL) return;
    abpDestruir(raiz->esq);   /* libera filhos antes do proprio no */
    abpDestruir(raiz->dir);
    free(raiz);
}

void abpEmOrdem(const NodoArv *raiz) {
    if (raiz == NULL) return;
    abpEmOrdem(raiz->esq);
    printf("%d ", raiz->dado.cod);
    abpEmOrdem(raiz->dir);
}

/* ================================================================
   Caminhamentos (Aula 11)
================================================================ */

void preOrdem(const NodoArv *raiz) {
    if (raiz == NULL) return;
    printf("%d ", raiz->dado.cod);   /* 1. visita a RAIZ (antes)  */
    preOrdem(raiz->esq);             /* 2. depois a esquerda      */
    preOrdem(raiz->dir);             /* 3. depois a direita       */
}

/* tambem chamado: central */
void emOrdem(const NodoArv *raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esq);              /* 1. primeiro a esquerda    */
    printf("%d ", raiz->dado.cod);   /* 2. visita a RAIZ (meio)   */
    emOrdem(raiz->dir);              /* 3. depois a direita       */
}

void posOrdem(const NodoArv *raiz) {
    if (raiz == NULL) return;
    posOrdem(raiz->esq);             /* 1. primeiro a esquerda    */
    posOrdem(raiz->dir);             /* 2. depois a direita       */
    printf("%d ", raiz->dado.cod);   /* 3. visita a RAIZ (depois) */
}

/* BFS: usa FilaArv (fila de enderecos de nos, adaptada de FilaEnc) */
void emNivel(NodoArv *raiz) {
    FilaArv fila;
    NodoArv *no;

    inicializaArv(&fila);
    if (raiz != NULL) enqueueArv(&fila, raiz);

    while (!estaVaziaArv(&fila)) {
        no = dequeueArv(&fila);
        printf("%d ", no->dado.cod);

        /* enqueue os filhos — serao visitados DEPOIS dos do nivel atual */
        if (no->esq != NULL) enqueueArv(&fila, no->esq);
        if (no->dir != NULL) enqueueArv(&fila, no->dir);
    }
}

/* ================================================================
   Exercicios da Aula 12
================================================================ */

/* convencao: arvore vazia tem altura -1; so a raiz tem altura 0 */
int abpAltura(const NodoArv *raiz) {
    int altEsq, altDir;
    if (raiz == NULL) return -1;
    altEsq = abpAltura(raiz->esq);
    altDir = abpAltura(raiz->dir);
    return 1 + (altEsq > altDir ? altEsq : altDir);
}

int abpContar(const NodoArv *raiz) {
    if (raiz == NULL) return 0;
    return 1 + abpContar(raiz->esq) + abpContar(raiz->dir);
}

int abpContarFolhas(const NodoArv *raiz) {
    if (raiz == NULL) return 0;
    if (raiz->esq == NULL && raiz->dir == NULL) return 1;
    return abpContarFolhas(raiz->esq) + abpContarFolhas(raiz->dir);
}

/* imprime em ordem crescente os nos com dado.cod em [a, b],
   podando subarvores que nao podem conter valores no intervalo */
void abpImprimirEntre(const NodoArv *raiz, int a, int b) {
    if (raiz == NULL) return;
    if (raiz->dado.cod > a)
        abpImprimirEntre(raiz->esq, a, b);
    if (raiz->dado.cod >= a && raiz->dado.cod <= b)
        printf("%d ", raiz->dado.cod);
    if (raiz->dado.cod < b)
        abpImprimirEntre(raiz->dir, a, b);
}

int abpSomaChaves(const NodoArv *raiz) {
    if (raiz == NULL) return 0;
    return raiz->dado.cod
         + abpSomaChaves(raiz->esq)
         + abpSomaChaves(raiz->dir);
}

/* conta nos com dado.cod > val, usando propriedade da Abp para podar */
int abpContarMaiores(const NodoArv *raiz, int val) {
    if (raiz == NULL) return 0;
    if (raiz->dado.cod <= val)
        /* este no e toda subarvore esquerda sao <= val */
        return abpContarMaiores(raiz->dir, val);
    return 1 + abpContarMaiores(raiz->dir, val)
             + abpContarMaiores(raiz->esq, val);
}

/* copia profunda: aloca novos nos com malloc */
NodoArv* abpCopiar(const NodoArv *raiz) {
    NodoArv *novo;
    if (raiz == NULL) return NULL;
    novo       = (NodoArv*) malloc(sizeof(NodoArv));
    novo->dado = raiz->dado;
    novo->esq  = abpCopiar(raiz->esq);
    novo->dir  = abpCopiar(raiz->dir);
    return novo;
}

int abpEstahPresente(const NodoArv *raiz, int cod) {
    if (raiz == NULL)          return 0;
    if (cod == raiz->dado.cod) return 1;
    if (cod < raiz->dado.cod)
        return abpEstahPresente(raiz->esq, cod);
    return abpEstahPresente(raiz->dir, cod);
}

/* ================================================================
   Exercicios do simulado para a prova 1 (área 1)
================================================================ */

// C1
// Retorna 1 se todos os codigos forem par; senao, retorna 0
int abpTodosPares(const NodoArv *raiz) {

    if (raiz == NULL) return 1;

    if (raiz->dado.cod % 2 != 0) return 0;

    return abpTodosPares(raiz->esq) && abpTodosPares(raiz->dir);

    // short-circuit evaluation: caso abpTodosPares(raiz->esq) retornar 0, então abpTodosPares(raiz->dir) não será chamada.
}

// C2
// Retorna a quantidade de nodos com exatamente UM filho
int abpContarComUmFilho(const NodoArv *raiz) {

    int count;

    if (raiz == NULL) return 0;

    count = abpContarComUmFilho(raiz->esq) + abpContarComUmFilho(raiz->dir);

    if (raiz->esq == NULL && raiz->dir != NULL) count++;
    if (raiz->esq != NULL && raiz->dir == NULL) count++;

    return count;
}

// C3
// Retorna a quantidade de nodos cujo código é estritamente menor que X
int abpContarMenoresQue(const NodoArv *raiz, int x) {

    // caso base
    if (raiz == NULL) return 0;

    // caso a raiz seja maior que x, podemos "podar a arvore direita - pois ela contem valores maiores" e contar somente a esquerda
    if (raiz->dado.cod >= x) return abpContarMenoresQue(raiz->esq, x);

    // caso a raiz seja menor que x, somamos 1 e continuamos a recursão nos filhos
    return 1 + abpContarMenoresQue(raiz->esq, x) + abpContarMenoresQue(raiz->dir, x);
}

// C4
// Retorna o maior codigo (assumindo arvora nao vazia)
int abpMaiorCod(const NodoArv *raiz) {

    if (raiz->dir == NULL) return raiz->dado.cod;

    return abpMaiorCod(raiz->dir);
}

// C5
// Imprime em ordem crescente todos os produtos com cod ∈ [minCod, maxCod]
void abpImprimirIntervalo(const NodoArv *raiz, int minCod, int maxCod) {

    if (raiz == NULL) return;

    // in-order: ERD
    
    if (raiz->dado.cod < minCod) return abpImprimirIntervalo(raiz->dir, minCod, maxCod);
    if (raiz->dado.cod > maxCod) return abpImprimirIntervalo(raiz->esq, minCod, maxCod);

    abpImprimirIntervalo(raiz->esq, minCod, maxCod);

    printf("cod: %d - nome: %s - preco: %.2f\n", raiz->dado.cod, raiz->dado.nome, raiz->dado.preco);

    abpImprimirIntervalo(raiz->dir, minCod, maxCod);

    return;
}

// C6
// Retorna a quantidade de produtos cujo código é estritamente maior que x
int abpContarMaioresQue(const NodoArv *raiz, int x) {
    if (raiz == NULL) return 0;

    if (raiz->dado.cod <= x) return abpContarMaioresQue(raiz->dir, x);

    return 1 + abpContarMaioresQue(raiz->esq, x) + abpContarMaioresQue(raiz->dir, x);
}

// C7
// Retorna 1 se existir pelo menos um produto com cod ∈ [minCod, maxCod], e 0 caso contrário
int abpExisteNoIntervalo(const NodoArv *raiz, int minCod, int maxCod) {
    
    if (raiz == NULL) return 0;
    if (raiz->dado.cod >= minCod && raiz->dado.cod <= maxCod) return 1;

    if (raiz->dado.cod < minCod) return abpExisteNoIntervalo(raiz->dir, minCod, maxCod);
    return abpExisteNoIntervalo(raiz->esq, minCod, maxCod);
}

// C8
// Retorna a soma de todos os codigos
int abpSomaCods(const NodoArv *raiz) {
    if (raiz == NULL) return 0;

    return raiz->dado.cod + abpSomaCods(raiz->esq) + abpSomaCods(raiz->dir);
}