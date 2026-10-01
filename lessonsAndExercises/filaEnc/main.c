#include <stdio.h>
#include "filaEnc.h"

int main() {
    FilaEnc f;
    Produto p1 = {1, "Produto A", 10.0f};
    Produto p2 = {2, "Produto B", 20.0f};
    Produto p3 = {3, "Produto C", 30.0f};
    Produto p4 = {4, "Produto C", 30.0f};
    Produto p5 = {4, "Produto C", 30.0f};
    Produto p6 = {6, "Produto E", 30.0f};
    Produto removido;

    inicializa(&f);

    enfileira(&f, p1); // fila: [A]
    enfileira(&f, p2); // fila: [A, B]
    enfileira(&f, p3); // fila: [A, B, C]

    printf("Tamanho: %d\n", tamanho(&f)); // imprime 3

    removerDaFilaPorCod(&f, 2);

    printf("Tamanho: %d\n", tamanho(&f)); // imprime 2

    printf("\nTEM CONSECUTIVOS IGUAIS?\n");
    enfileira(&f, p4);
    enfileira(&f, p5);
    enfileira(&f, p6);
    printf("%d\n", temConsecutivosIguais(&f));

    while (!estaVazia(&f)) { // libera o restante da fila, nodo a nodo
        desenfileira(&f, &removido);
    }

    return 0;
}
