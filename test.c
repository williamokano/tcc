#include <stdio.h>
#include <stdlib.h>
#include "headers/graphics.h"

void showMenu();

int main() {
    inicializarBiblioteca();

    retangulo(point2d(0, 0), 200, 100);
    limparTela();

    ponto(point2d(100, 100), 20);

    definirCor(255, 122, 0);
    quadrado(point2d(40, 40), 50);

    getchar();
    return 0;
}