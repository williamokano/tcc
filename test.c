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
    definirTamanho(25);
    ponto(100, 100);

    definirCor(corOriginal[0], corOriginal[1], corOriginal[2]);
    quadrado(40, 40, 50);

    definirCor(255, 0, 0);
    //triangulo(100, 100, 100, 300, 200, 300);
    definirTamanho(5);
    ponto(100, 100);
    ponto(300, 100);
    ponto(200, 300);

    definirCor(0, 0, 255);
    triangulo(100, 100, 300, 100, 200, 300);

    definirCor(255, 255, 255);
    ponto(200, 175);

    definirCor(175, 175, 0);
    GLfloat vertices[] = {
        320, 100,
        400, 300,
        800, 50,
        520, 10,
        340, 40
    };
    poligono(5, vertices);

    // Desenha um ponto em cada vertice do polígono
    definirCor(255, 0, 0);
    for (int i = 0; i < 5; i++) {
        ponto(vertices[(i * 2) + 0], vertices[(i * 2) + 1]);
    }

    getchar();
    return 0;
}