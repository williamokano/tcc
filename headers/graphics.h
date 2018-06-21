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
void ponto(int x, int y);
void triangulo(Point2D p1, Point2D p2, Point2D p3);
void retangulo(Point2D position, int width, int height);
void quadrado(Point2D position, int side);
void pausar(int time);

#endif // GRAPHICS_H_INCLUDED
