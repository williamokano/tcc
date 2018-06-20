#include <stdio.h>
#include <stdlib.h>
#include "headers/graphics.h"

void showMenu();
void inserirPonto();
void inserirTriangulo();
void trocarCor();

int main() {
    initWindow();

    while(1) {
        showMenu();
    }

    getchar();
    return 0;
}

void showMenu() {
    int opcao, x, y, z;

    do {
        printf("[1] - Inserir ponto\n");
        printf("[2] - Inserir triangulo\n");
        printf("[3] - Trocar cor\n");
        printf("[8] - Limpar\n");
        printf("[9] - Trocar sair\n");
        scanf("%d", &opcao);
    } while(opcao < 1 || opcao > 9);

    switch (opcao) {
        case 1: inserirPonto(); break;
        case 2: inserirTriangulo(); break;
        case 3: trocarCor(); break;

        case 8: clear(); break;
        case 9: printf("Sayonara\n"); exit(-1);
        
        default:
            printf("Opção não faz nada ainda.\n");
    }
}

void inserirPonto() {
    int x, y, size;
    printf("Enter X and Y position and Size\n");
    scanf("%d %d %d", &x, &y, &size);
    point(point2d(x, y), size);
}

void inserirTriangulo() {

}

void trocarCor() {

}