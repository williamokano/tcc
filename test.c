#include <stdio.h>
#include "headers/graphics.h"

void showMenu();

int main() {
    inicializarBiblioteca(1366, 768);

    linha(
        0, 0,
        1366, 768
    );

    getchar();
    return 0;
}