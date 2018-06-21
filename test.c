#include <stdio.h>
#include <stdlib.h>
#include "headers/graphics.h"

void showMenu();

int main() {
    inicializarBiblioteca();

    definirCor(255, 0, 255);
    retangulo(point2d(0, 0), 200, 100);
    limparTela();

    int* corOriginal = obterCor();

    definirCor(255, 122, 0);
    ponto(point2d(100, 100), 20);

    definirCor(corOriginal[0], corOriginal[1], corOriginal[2]);
    quadrado(point2d(40, 40), 50);

    getchar();
    return 0;
}