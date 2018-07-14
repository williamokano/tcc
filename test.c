#include <stdio.h>
#include "headers/graphics.h"

void showMenu();

int main() {
    inicializarBiblioteca(500, 500);

    definirCor(0, 0, 255);
    poligonoRegular(100, 100, 50, 3);

    definirCor(255, 0, 0);
    poligonoRegular(200, 200, 65, 4);

    definirCor(0, 255, 0);
    poligonoRegular(300, 300, 38, 5);

    definirCor(255, 255, 0);
    poligonoRegular(400, 400, 50, 6);

    getchar();
    return 0;
}