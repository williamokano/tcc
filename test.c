#include <stdio.h>
#include <stdlib.h>
#include "headers/graphics.h"

void showMenu();

int main() {
    inicializarBiblioteca();

    definirCor(255, 0, 255);
    retangulo(0, 0, 200, 100);
    limparTela();

    int* corOriginal = obterCor();

    definirCor(255, 122, 0);
    definirTamanho(50);
    ponto(100, 100);

    definirCor(corOriginal[0], corOriginal[1], corOriginal[2]);
    quadrado(40, 40, 50);

    getchar();
    return 0;
}