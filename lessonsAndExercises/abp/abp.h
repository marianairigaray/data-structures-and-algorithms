#ifndef ABP_H
#define ABP_H

#include "produto.h"

typedef struct str_NodoArv NodoArv;

struct str_NodoArv {
    Produto  dado;
    NodoArv *esq;
    NodoArv *dir;
};

/* ----------------------------------------------------------------
   TAD AbpProduto
   A arvore e representada pelo ponteiro NodoArv *raiz (sem descritor).
   Operacoes que modificam a arvore RETORNAM o novo ponteiro raiz;
   o chamador deve reatribuir sua variavel:
       raiz = abpInserir(raiz, p);
---------------------------------------------------------------- */

NodoArv* abpCriar    (void);
NodoArv* abpBuscar   (NodoArv *raiz, int cod);
NodoArv* abpInserir  (NodoArv *raiz, Produto p);
NodoArv* abpRemover  (NodoArv *raiz, int cod);
void     abpDestruir (NodoArv *raiz);
void     abpEmOrdem  (const NodoArv *raiz);   /* imprime em ordem crescente */

/* ----------------------------------------------------------------
   Caminhamentos (Aula 11)
---------------------------------------------------------------- */

void preOrdem (const NodoArv *raiz);   /* raiz, esq, dir            */
void emOrdem  (const NodoArv *raiz);   /* esq, raiz, dir  (central) */
void posOrdem (const NodoArv *raiz);   /* esq, dir, raiz            */
void emNivel  (NodoArv *raiz);         /* BFS nivel a nivel         */

/* ----------------------------------------------------------------
   Exercicios da Aula 12
---------------------------------------------------------------- */

int      abpAltura            (const NodoArv *raiz);
int      abpContar            (const NodoArv *raiz);
int      abpContarFolhas      (const NodoArv *raiz);
void     abpImprimirEntre     (const NodoArv *raiz, int a, int b);
int      abpSomaChaves        (const NodoArv *raiz);
int      abpContarMaiores     (const NodoArv *raiz, int val);
NodoArv* abpCopiar            (const NodoArv *raiz);
int      abpEstahPresente     (const NodoArv *raiz, int cod);

/* ----------------------------------------------------------------
   Exercicios do simulado para a prova 1 (área 1)
---------------------------------------------------------------- */

int      abpTodosPares        (const NodoArv *raiz);
int      abpContarComUmFilho  (const NodoArv *raiz);
int      abpContarMenoresQue  (const NodoArv *raiz, int x);
int      abpMaiorCod          (const NodoArv *raiz);
void     abpImprimirIntervalo (const NodoArv *raiz, int minCod, int maxCod);
int      abpContarMaioresQue  (const NodoArv *raiz, int x);
int      abpExisteNoIntervalo (const NodoArv *raiz, int minCod, int maxCod);
int      abpSomaCods          (const NodoArv *raiz);

#endif
