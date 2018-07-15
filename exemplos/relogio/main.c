#include <stdio.h>
#include <time.h>
#include <math.h>
#include "headers/graphics.h"

// Por questões de compabilidade interoperacional defino meu próprio PI com precisão de 64 bits
#define CUSTOM_PI 3.1415926535897932384626433832795028841971693993751058209749445
#define M_RAD CUSTOM_PI / 180.0f

void showMenu();

int main() {
    inicializarBiblioteca(800, 600);
    time_t now;
    struct tm *now_tm;
    int hour;
    int minute;
    int seconds;
    float passo;
    int middleX = 400;
    int middleY = 300;
    int tamanhoPonteiro = 300;
    int rotacao;

    int tmpPX, tmpPY;

    while(1) {
        now = time(NULL);
        now_tm = localtime(&now);
        hour = now_tm->tm_hour % 12;
        minute = now_tm->tm_min;
        seconds = now_tm->tm_sec;
        
        limparTela();

        // Desenha a base do relógio
        definirCor(255, 255, 255);
        circulo(400, 300, 300);
        definirCor(0, 0, 0);
        circulo(400, 300, 3);

        // Desenha os pontos de 12, 3, 6 e 9 horas
        definirCor(0, 0, 0);
        definirTamanho(20);
        ponto(400, 20);
        ponto(400, 580);
        ponto(120, 300);
        ponto(680, 300);

        // Ponteiro horas
        passo = 360.0f / 12;
        rotacao = 12 / 4;
        tamanhoPonteiro = 220;
        tmpPX = middleX + (cos(M_RAD * (hour + rotacao) * passo) * -tamanhoPonteiro);
        tmpPY = middleY + (sin(M_RAD * (hour + rotacao) * passo) * tamanhoPonteiro);
        definirCor(255, 0, 0);
        definirTamanho(20);
        linha(
            middleX, middleY,
            tmpPX, tmpPY
        );

        // Ponteiro minutos
        passo = 360.0f / 60;
        rotacao = 60 / 4;
        tamanhoPonteiro = 280;
        tmpPX = middleX + (cos(M_RAD * (minute + rotacao) * passo) * -tamanhoPonteiro);
        tmpPY = middleY + (sin(M_RAD * (minute + rotacao) * passo) * tamanhoPonteiro);
        definirCor(0, 255, 0);
        definirTamanho(10);
        linha(
            middleX, middleY,
            tmpPX, tmpPY
        );

        // Ponteiro dos segundos
        passo = 360.0f / 60;
        rotacao = 60 / 4;
        tamanhoPonteiro = 280;
        tmpPX = middleX + (cos(M_RAD * (seconds + rotacao) * passo) * -tamanhoPonteiro);
        tmpPY = middleY + (sin(M_RAD * (seconds + rotacao) * passo) * tamanhoPonteiro);
        definirCor(0, 0, 255);
        definirTamanho(2);
        linha(
            middleX, middleY,
            tmpPX, tmpPY
        );

        pausar(1);
    }

    getchar();
    return 0;
}