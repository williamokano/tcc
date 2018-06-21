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
void definirCor(Point3D color);
Point3D obterCor();

void ponto(Point2D position, int size);
void triangulo(Point2D p1, Point2D p2, Point2D p3);
void retangulo(Point2D position, int width, int height);
void quadrado(Point2D position, int side);
void pausar(int time);

#endif // GRAPHICS_H_INCLUDED
