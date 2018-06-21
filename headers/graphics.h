#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <GLFW/glfw3.h>
#include "tinycthread.h"
#include "shape.h"

// Screen stuff
void inicializarBiblioteca();
int bibliotecaInicializada();
void limparTela();
void desfazerUltimaForma();
void refazerUltimaForma();

// Color stuff
void definirCor(int vermelho, int verde, int azul);
int* obterCor();

// Size stuff
void definirTamanho(int tamanho);
int obterTamanho();

// Drawing stuff
void poligono(int numeroDeVertices, GLfloat* posicoes);
void ponto(int posX, int posY);
void triangulo(int posX1, int posY1, int posX2, int posY2, int posX3, int posY3);
void retangulo(int posX, int posY, int width, int height);
void quadrado(int posX, int posY, int tamanhoLado);
void poligonoRegular(int posX, int posY, int raio, int faces);
void circulo(int posX, int posY, int raio);
void pentagono(int posX, int posY, int raio);
void hexagono(int posX, int posY, int raio);
void decagono(int posX, int posY, int raio);
void dodecagono(int posX, int posY, int raio);

// Common stuff
void pausar(int time);

#endif // GRAPHICS_H_INCLUDED
