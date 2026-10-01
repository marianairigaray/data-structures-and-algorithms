#include <stdio.h>
#include <stdlib.h>
#include "listaEnc.h"

void inicializar(ListaEnc *lista) {
    lista->ini = NULL;
}

int tamanho(const ListaEnc *lista) {
    Nodo *aux = lista->ini;
    int contador = 0;

    while (aux != NULL) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}

void imprimir(const ListaEnc *lista) {
    Nodo *aux;
    aux = lista->ini;

    while (aux != NULL) {
        printf("Codigo: %d\n", aux->dado.cod);
        printf("Nome: %s\n", aux->dado.nome);
        printf("Preco: %f\n", aux->dado.preco);
        aux = aux->prox;
    }
}

Produto buscar(const ListaEnc *lista, int cod) {
    Nodo *aux;
    Produto prod = {0, "", 0.0f};
    aux = lista->ini;

    while (aux != NULL) {
        if (aux->dado.cod == cod)
            return aux->dado;
        aux = aux->prox;
    }

    return prod; // não encontrado: produto "vazio"
}

int inserirInicio(ListaEnc *lista, Produto prod) {
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo == NULL)
        return 0; // falha na alocação

    novo->dado = prod;
    novo->prox = lista->ini; // o novo nodo aponta para o antigo início
    lista->ini = novo;        // o novo nodo passa a ser o início

    return 1;
}

int inserirFim(ListaEnc *lista, Produto prod) {
    Nodo *novo;
    Nodo *aux;

    novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo == NULL)
        return 0;

    novo->dado = prod;
    novo->prox = NULL;

    if (lista->ini == NULL) { // lista vazia: o novo nodo é o único (e o início)
        lista->ini = novo;
    } else {
        aux = lista->ini;
        while (aux->prox != NULL) // percorre até o último nodo
            aux = aux->prox;
        aux->prox = novo;
    }

    return 1;
}

int removerPorCod(ListaEnc *lista, int cod) {
    Nodo *ant;
    Nodo *aux;

    ant = NULL;
    aux = lista->ini;

    while (aux != NULL && aux->dado.cod != cod) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) // não encontrado
        return 0;

    if (ant == NULL) // removendo o primeiro nodo
        lista->ini = aux->prox;
    else             // removendo do meio ou do final
        ant->prox = aux->prox;

    free(aux);
    return 1;
}

void destruir(ListaEnc *lista) {
    Nodo *ant;
    Nodo *aux;
    aux = lista->ini;

    while (aux != NULL) {
        ant = aux;
        aux = aux->prox;
        free(ant);
    }

    lista->ini = NULL;
}

// TODO: PODE-SE MELHORAR A LÓGICA DESSA FUNÇÃO (OLHAR SOLUÇÃO DO SOR DENNIS)
void removerMenoresQuePreco(ListaEnc *lista, float p) {
    if (lista->ini == NULL) return;

    Nodo *atual = lista->ini;
    Nodo *anterior = NULL;

    while(atual != NULL) {

        if (atual->dado.preco < p) {

            // caso 1: remover o primeiro nodo
            if (anterior == NULL) {
                lista->ini = atual->prox;

                // remove o nodo atual
                free(atual);

                // passa para o proximo nodo para dar continuidade na iteração da lista
                atual = lista->ini;
            }
            // caso 2: remover nodo "no meio" ou no final da lista
            else {
                anterior->prox = atual->prox;
                
                // remove o nodo atual
                free(atual);

                // passa para o proximo nodo para dar continuidade na iteração da lista
                atual = anterior->prox;
            }
        }
        else {
            anterior = atual;
            atual = atual->prox;
        }
    }

    return;
}

void concatenarListas(ListaEnc *a, const ListaEnc *b) {
    
    if (b->ini == NULL) return;

    if (a->ini == NULL) {
        a->ini = b->ini;
        return;
    }

    // itera ate o último nodo da lista
    Nodo *atual = a->ini;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    // atribui ao prox do ultimo nodo o primeiro nodo de B    
    atual->prox = b->ini;
}

void inverterLista(ListaEnc *lista) {
    
}