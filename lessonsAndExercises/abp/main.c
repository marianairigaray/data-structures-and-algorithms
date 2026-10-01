#include <stdio.h>
#include <string.h>
#include "abp.h"

static Produto makeProduto(int cod, const char *nome, float preco) {
    Produto p;
    p.cod   = cod;
    strncpy(p.nome, nome, sizeof(p.nome) - 1);
    p.nome[sizeof(p.nome) - 1] = '\0';
    p.preco = preco;
    return p;
}

int main(void) {
    NodoArv *raiz = abpCriar();

    /* insere: 50 30 70 20 40 60 80 */
    raiz = abpInserir(raiz, makeProduto(50, "P50", 5.0f));
    raiz = abpInserir(raiz, makeProduto(30, "P30", 3.0f));
    raiz = abpInserir(raiz, makeProduto(70, "P70", 7.0f));
    raiz = abpInserir(raiz, makeProduto(20, "P20", 2.0f));
    raiz = abpInserir(raiz, makeProduto(40, "P40", 4.0f));
    raiz = abpInserir(raiz, makeProduto(60, "P60", 6.0f));
    raiz = abpInserir(raiz, makeProduto(80, "P80", 8.0f));

    /*
            50
           /  \
         30    70
        /  \  /  \
      20  40 60  80
    */

    printf("Pre-ordem:  "); preOrdem(raiz); printf("\n");
    /* esperado: 50 30 20 40 70 60 80 */

    printf("Em-ordem:   "); emOrdem(raiz);  printf("\n");
    /* esperado: 20 30 40 50 60 70 80  (ordem crescente) */

    printf("Pos-ordem:  "); posOrdem(raiz); printf("\n");
    /* esperado: 20 40 30 60 80 70 50 */

    printf("Em nivel:   "); emNivel(raiz);  printf("\n");
    /* esperado: 50 30 70 20 40 60 80 */

    printf("Altura:     %d\n", abpAltura(raiz));       /* 2 */
    printf("Nos:        %d\n", abpContar(raiz));        /* 7 */
    printf("Folhas:     %d\n", abpContarFolhas(raiz));  /* 4 */
    printf("Soma chaves:%d\n", abpSomaChaves(raiz));    /* 350 */

    printf("Entre [25,65]: ");
    abpImprimirEntre(raiz, 25, 65);
    printf("\n");
    /* esperado: 30 40 50 60 */

    printf("Maiores que 45: %d\n", abpContarMaiores(raiz, 45)); /* 3 */

    printf("Presente 40: %d\n", abpEstahPresente(raiz, 40)); /* 1 */
    printf("Presente 99: %d\n", abpEstahPresente(raiz, 99)); /* 0 */

    /* remove 30 (dois filhos) */
    raiz = abpRemover(raiz, 30);
    printf("Apos remover 30 (em-ordem): "); emOrdem(raiz); printf("\n");
    /* esperado: 20 40 50 60 70 80 */

    abpDestruir(raiz);
    raiz = NULL;


    /* ================================================================
      Exercicios do simulado para a prova 1 (área 1)
    ================================================================ */

    printf("\n");
    printf("================================================================\n");
    printf("Exercicios do simulado para a prova 1 (area 1)\n");
    printf("================================================================\n");

    raiz = abpCriar();

    /* insere: 50 30 70 20 40 60 80 */
    raiz = abpInserir(raiz, makeProduto(50, "P50", 5.0f));
    raiz = abpInserir(raiz, makeProduto(30, "P30", 3.0f));
    raiz = abpInserir(raiz, makeProduto(70, "P70", 7.0f));
    raiz = abpInserir(raiz, makeProduto(20, "P20", 2.0f));
    raiz = abpInserir(raiz, makeProduto(60, "P60", 6.0f));
    raiz = abpInserir(raiz, makeProduto(80, "P80", 8.0f));
    raiz = abpInserir(raiz, makeProduto(90, "P90", 9.0f));

    /*
            50
           /  \
         30    70
        /     /  \
      20     60  80
                   \
                   90
    */

    printf("Em-ordem:   "); emOrdem(raiz);  printf("\n");
    /* esperado: 20 30 50 60 70 80 90  (ordem crescente) */

    // C2
    printf("Numero de nodos com apenas um filho: %d\n", abpContarComUmFilho(raiz));

    // C3
    int x = 50;
    printf("Numero de nodos menores que %d: %d\n", x, abpContarMenoresQue(raiz, x));

    // C4
    printf("Maior codigo da arvore: %d\n", abpMaiorCod(raiz));

    // C5
    printf("Imprime arvore no intervalo de [30, 70] em ordem:\n"); 
    abpImprimirIntervalo(raiz, 30, 70);

    // C6
    raiz = abpInserir(raiz, makeProduto(40, "P40", 4.0f));
    /*
            50
           /  \
         30    70
        /  \   /  \
      20   40 60  80
                   \
                   90
    */
    printf("Adicao de 40 a arvore (em ordem):   "); emOrdem(raiz);  printf("\n");
    /* esperado: 20 30 40 50 60 70 80 90  (ordem crescente) */
    x = 39;
    printf("Numero de nodos maiores que %d: %d\n", x, abpContarMaioresQue(raiz, x));

    // C7
    printf("Existencia de pelo menos um produto com codigo entre [40, 41]: %d\n", abpExisteNoIntervalo(raiz, 40, 41));

    // C8
    printf("Soma de todos os codigos de produto da arvore: %d\n", abpSomaCods(raiz));

    return 0;
}
