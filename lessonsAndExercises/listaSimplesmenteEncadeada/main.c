#include <stdio.h>
#include "listaEnc.h"

int main() {
    ListaEnc lista;
    inicializar(&lista);

    Produto p1 = {1, "Produto A", 10.0f};
    Produto p2 = {2, "Produto B", 50.0f};
    Produto p3 = {2, "Produto C", 40.0f};
    Produto p4 = {2, "Produto D", 50.0f};
    Produto p5 = {2, "Produto E", 20.0f};

    inserirInicio(&lista, p1); // lista: [A]
    inserirFim(&lista, p2);    // lista: [A, B]
    inserirFim(&lista, p3);    // lista: [A, B, C]
    inserirFim(&lista, p4);    // lista: [A, B, C, D]
    inserirFim(&lista, p5);    // lista: [A, B, C, D, E]


    // DO INICIO
    removerMenoresQuePreco(&lista, 11.0);
    imprimir(&lista);
    printf("Tamanho: %d\n", tamanho(&lista)); // imprime 2
    printf("\n");

    // DO MEIO E DO FINAL
    removerMenoresQuePreco(&lista, 41.0);
    imprimir(&lista);
    printf("Tamanho: %d\n", tamanho(&lista)); // imprime 2
    printf("\n");

    // REMOVER TUDO
    removerMenoresQuePreco(&lista, 100.0);
    imprimir(&lista);
    printf("Tamanho: %d\n", tamanho(&lista)); // imprime 2
    printf("\n");

    buscar(&lista, 1);

    removerPorCod(&lista, 1);  // lista: [B]
    destruir(&lista);          // lista: vazia, memória liberada

    return 0;
}
