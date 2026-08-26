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

    int counter = 0;

    while (aux != NULL && counter != 5) {
        printf("Codigo: %d\n", aux->dado.cod);
        printf("Nome: %s\n", aux->dado.nome);
        printf("Preco: %.2f\n", aux->dado.preco);
        printf("-------\n");
        aux = aux->prox;
        counter++;
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

// Funções a implementar
int removerFim(ListaEnc *l, Produto *prodRemovido) {

    // Se a lista for vazia
    if ((l->ini) == NULL)
    {
        printf("Lista vazia!\n");
        return 0;
    }

    // Cria nodo auxiliar para percorrer a lista
    Nodo *aux;
    Nodo *ant;
    aux = l->ini;

    // Percorrer a lista até o último nodo
    while(aux->prox != NULL) {
        ant = aux;
        aux = aux->prox;
    }

    // Copia o conteúdo do último nodo no prodRemovido
    *prodRemovido = aux->dado;

    // Faz o peno-último item da lista apontar para NULL
    ant->prox = NULL;

    // Libera o último
    free(aux);

    return 1;
}

int trocarComProximo(ListaEnc *l, int pos) {

    // Cria nodo auxiliar para percorrer a lista
    Nodo *aux;
    Nodo *ant;

    // aux recebe o endereço do primeiro nodo da lista
    aux = l->ini;

    // ainda n existe nodo anterior a aux
    ant = NULL;

    // Contador
    int counter = 0;

    // Começa no zero
    // Troca o n pelo próximo

    // Percorrer a lista até pos ou até chegar no último nodo
    while(aux != NULL && counter != pos) {
        ant = aux;
        aux = aux->prox;
        counter++;
    }

    if (aux == NULL) // não encontrado
        return 0;

    if (aux->prox == NULL) // última posição - impossível de trocar com o próximo
        return 0;

    if (ant == NULL) { // troca primeiro nodo com o segundo

        // define o segundo nodo como o inicio da lista
        l->ini = aux->prox;

        // faz o "primeiro nodo" apontar para o terceiro nodo
        aux->prox = aux->prox->prox;

        // define o "primeiro" nodo da lista como segundo nodo da lista
        l->ini->prox = aux;

        return 1;
    }

    // troca o nodo com o próximo nodo (em algum ponto no meio da lista)

    // o nodo anterior aponta para o nodo counter + 1
    ant->prox = aux->prox;

    // o nodo counter aponta para o nodo couter + 2
    aux->prox = aux->prox->prox;

    // o nodo counter + 1 (antigo proximo) aponta para o counter
    ant->prox->prox = aux;

    return 1;
}
