#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <GLFW/glfw3.h>
#include "tinycthread.h"
#include "point.h"
#include "shape.h"

void inicializarBiblioteca();
int bibliotecaInicializada();
void limparTela();

// Color stuff
void definirCor(int vermelho, int verde, int azul);
int* obterCor();

// Size stuff
void definirTamanho(int tamanho);
int obterTamanho();

// Drawing stuff
void poligono(int numeroDeVertices, GLfloat* posicoes);
void ponto(int posX, int posY);
void triangulo(Point2D p1, Point2D p2, Point2D p3);
void retangulo(int posX, int posY, int width, int height);
void quadrado(int posX, int posY, int tamanhoLado);
void pausar(int time);

#endif // GRAPHICS_H_INCLUDED
