#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/graphics.h"

#define SHAPES_MAX_SIZE 100
#define TIPO_FORMA_2D 2
#define VERTICES(QTD) QTD

// Por questões de compabilidade interoperacional defino meu próprio PI com precisão de 64 bits
#define CUSTOM_PI 3.1415926535897932384626433832795028841971693993751058209749445
#define M_RAD CUSTOM_PI / 180.0f

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*                       SLEEP HACK                       */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h> // for usleep
#endif
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*                    GLOBAL VARIABLES                    */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
thrd_t hiddenThread;
mtx_t shapesMutex;
mtx_t globalsMutex;

GLFWwindow* hiddenWindow = NULL;
int larguraJanela = 800;
int alturaJanela = 600;

Shape* shapes = NULL;
int numOfShapes = 0;

int vermelhoGlobal = 255;
int verdeGlobal = 255;
int azulGlobal = 255;

int tamanhoGlobal = 1;
int larguraGlobal = 1;
int shapeAfterUndo = 0;
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

void error_callback(int error, const char* description);
void controls(GLFWwindow *window, int key, int scancode, int action, int mods);
int hiddenMainLoop(void* args);
void drawBuffer();

void inicializarFormas() {
    mtx_lock(&shapesMutex);
    shapes = malloc(SHAPES_MAX_SIZE * sizeof(Shape));
    mtx_unlock(&shapesMutex);
}

void addShape(Shape shape) {
    mtx_lock(&shapesMutex);
    shapes[numOfShapes++] = shape;
    shapeAfterUndo = 1;
    mtx_unlock(&shapesMutex);
}

void limparFormas() {
    mtx_lock(&shapesMutex);
    // TODO: free memory
    numOfShapes = 0;
    mtx_unlock(&shapesMutex);
}

GLfloat* colorHelper(int numOfVertices) {
    return shapeColor(numOfVertices, vermelhoGlobal, verdeGlobal, azulGlobal);
}

Shape createShapeHelper(
    const char drawType,
    int numeroDeVertices,
    GLfloat* vertices
) {
    return createShape(
        drawType,
        numeroDeVertices,
        vertices,
        obterTamanho(),
        TIPO_FORMA_2D,
        colorHelper(numeroDeVertices));
}

void inicializarBiblioteca(int largura, int altura) {
    larguraJanela = largura;
    alturaJanela = altura;

    if (thrd_create(&hiddenThread, hiddenMainLoop, (void*)0) != thrd_success) {
        fprintf(stderr, "Falha ao inicializar hiddenMainLoop\n");
        exit(-1);
    }
    #ifdef DEBUG
    else {
        fprintf(stdout, "Window reported initalized\n");
    }
    #endif

    if (mtx_init(&shapesMutex, mtx_plain) != thrd_success) {
        fprintf(stderr, "Falha ao criar mutex de formas\n");
        exit(-1);
    }

    if (mtx_init(&globalsMutex, mtx_plain) != thrd_success) {
        fprintf(stderr, "Falha ao criar mutex de globais\n");
        exit(-1);
    }

    inicializarFormas();
}

int bibliotecaInicializada() {
    return hiddenWindow != NULL;
}

void limparTela() {
    limparFormas();
}

void desfazerUltimaForma() {
    mtx_lock(&shapesMutex);
    if (numOfShapes > 0) {
        numOfShapes--;
        shapeAfterUndo = 0; // Reset undo counter. useful when trying to redo things
    }
    mtx_unlock(&shapesMutex);
}

void refazerUltimaForma() {
    mtx_lock(&shapesMutex);
    if (shapeAfterUndo == 0) {
        numOfShapes++;
    }
    mtx_unlock(&shapesMutex);
}

void definirCor(int vermelho, int verde, int azul) {
    vermelhoGlobal = vermelho;
    verdeGlobal = verde;
    azulGlobal = azul;
}

int* obterCor() {
    int* coresGlobais = (int*) malloc(3 * sizeof(int));
    
    coresGlobais[0] = vermelhoGlobal;
    coresGlobais[1] = verdeGlobal;
    coresGlobais[2] = azulGlobal;

    return coresGlobais;
}

// Size stuff
void definirTamanho(int tamanho) {
    mtx_lock(&globalsMutex);
    tamanhoGlobal = tamanho;
    mtx_unlock(&globalsMutex);
}

int obterTamanho() {
    int tamanhoNoMomentoDaLeitura;
    mtx_lock(&globalsMutex);
    tamanhoNoMomentoDaLeitura = tamanhoGlobal;
    mtx_unlock(&globalsMutex);

    return tamanhoNoMomentoDaLeitura;
}

void definirLargura(int largura) {
    mtx_lock(&globalsMutex);
    larguraGlobal = largura;
    mtx_unlock(&globalsMutex);
}

int obterLargura() {
    int larguraNoMomentoDaLeitura;
    mtx_lock(&globalsMutex);
    larguraNoMomentoDaLeitura = larguraGlobal;
    mtx_unlock(&globalsMutex);

    return larguraNoMomentoDaLeitura;
}

// Drawing stuff
void poligono(int numeroDeVertices, GLfloat* posicoes) {
    addShape(createShapeHelper(
        GL_POLYGON,
        numeroDeVertices,
        posicoes
    ));
}

void ponto(int posX, int posY) {
    GLfloat* vertices = malloc(2 * sizeof(GLfloat));
    vertices[0] = posX;
    vertices[1] = posY;
    const int UM_VERTICE = 1;

    addShape(createShapeHelper(
        GL_POINTS,
        VERTICES(1),
        vertices
    ));
}

void triangulo(int posX1, int posY1, int posX2, int posY2, int posX3, int posY3) {
    GLfloat* vertices = malloc(VERTICES(3) * sizeof(GLfloat) * 2);
    vertices[0] = posX1;
    vertices[1] = posY1;
    vertices[2] = posX2;
    vertices[3] = posY2;
    vertices[4] = posX3;
    vertices[5] = posY3;

    addShape(createShapeHelper(
        GL_TRIANGLES,
        VERTICES(3),
        vertices
    ));
}

void retangulo(int posX, int posY, int largura, int altura) {
    GLfloat* vertices = malloc(VERTICES(4) * 2 * sizeof(GLfloat));
    vertices[0] = posX;
    vertices[1] = posY;
    vertices[2] = posX + largura;
    vertices[3] = posY;
    vertices[4] = posX + largura;
    vertices[5] = posY + altura;
    vertices[6] = posX;
    vertices[7] = posY + altura;

    addShape(createShapeHelper(
        GL_QUADS,
        VERTICES(4),
        vertices
    ));
}

void quadrado(int posX, int posY, int tamanhoLado) {
    retangulo(posX, posY, tamanhoLado, tamanhoLado);
}

void poligonoRegular(int posX, int posY, int raio, int faces) {
    #ifdef DEBUG
    fprintf(stdout, "Desenhando um poligono regular de %d faces e raio %d\n", faces, raio);
    #endif
    GLfloat* vertices = malloc(2 * faces * sizeof(GLfloat));
    float passo = 360.0f / (float) faces;
    for (int i = 0; i < faces; i++) {
        vertices[(i * 2) + 0] = posX + (cos(M_RAD * i * passo) * raio); // Ponto X do vértice = ponto fixo X + cos(angulo) * raio
        vertices[(i * 2) + 1] = posY + (sin(M_RAD * i * passo) * raio); // Ponto Y do vértice = ponto fixo Y + sin(angulo) * raio

        #ifdef DEBUG
        fprintf(stdout, "Ponto %d: X: %f, Y: %f\n", i, vertices[(i * 2) + 0], vertices[(i * 2) + 1]);
        #endif
    }

    poligono(faces, vertices);
}

// Existem 2 meios de desenhar um círculo em OPEN_GL, usando o próprio polígono
// Ou utilizando GL_TRIANGLE_STRIPES, que são triangulos colados uns aos outros
// Optei por utilizar o polígono regular com 360 por achar mais fácil calcular os angulos dos pontos
void circulo(int posX, int posY, int raio) {
    poligonoRegular(posX, posY, raio, 360);
}

void pentagono(int posX, int posY, int raio) {
    poligonoRegular(posX, posY, raio, 5);
}

void hexagono(int posX, int posY, int raio) {
    poligonoRegular(posX, posY, raio, 6);
}

void decagono(int posX, int posY, int raio) {
    poligonoRegular(posX, posY, raio, 10);
}

void dodecagono(int posX, int posY, int raio) {
    poligonoRegular(posX, posY, raio, 12);
}

void linha(int posX1, int posY1, int posX2, int posY2) {
    GLfloat* vertices = malloc(VERTICES(2) * 2 * sizeof(GLfloat));
    vertices[0] = posX1;
    vertices[1] = posY1;
    vertices[2] = posX2;
    vertices[3] = posY2;

    addShape(createShapeHelper(
        GL_LINES,
        VERTICES(2),
        vertices
    ));
}

void pausar(int time) {
    #ifdef WIN32
    Sleep(time * 1000);
    #else
    sleep(time);
    #endif
}

int hiddenMainLoop(void* args) {
    #ifdef DEBUG
    fprintf(stdout, "hiddenMainLoop started\n");
    #endif

    glfwSetErrorCallback(error_callback);
    /* Initialize the library */
    if (!glfwInit()) {
        fprintf(stderr, "Failed to init GLFW\n");
        exit(-1);
    }
    #ifdef DEBUG
    else {
        fprintf(stdout, "GLFW initialized\n");
    }
    #endif

    /* Create a windowed mode window and its OpenGL context */
    #ifdef DEBUG
    fprintf(stdout, "Attempting to create window\n");
    #endif

    hiddenWindow = glfwCreateWindow(larguraJanela, alturaJanela, "Window", NULL, NULL);
    if (!hiddenWindow) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        exit(-1);
    }
    #ifdef DEBUG
    else {
        fprintf(stdout, "Window created\n");
    }
    #endif

    /* Make the window's context current */
    glfwMakeContextCurrent(hiddenWindow);
    glfwSetKeyCallback(hiddenWindow, controls);

    glViewport(0.0f, 0.0f, larguraJanela, alturaJanela);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, larguraJanela, 0, alturaJanela, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glfwSwapInterval(1); // Lock FPS at 60
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(hiddenWindow)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        drawBuffer();

        /* Swap front and back buffers */
        glfwSwapBuffers(hiddenWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    exit(0);
}

void drawBuffer() {

    // Ensure exclusive lock to avoid partial drawing, also know as tearing
    // new shapes cannot be added on the rendering process
    // Also the rendering cannot occur while adding new shapes, which should be blazing fast
    mtx_lock(&shapesMutex);
    for (int i = 0; i < numOfShapes; i++) {
        Shape shape = shapes[i];

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        switch(shape.drawType) {
            case GL_POINTS:
                glPointSize(shape.shapeSize);
            break;
            case GL_LINES:
                glLineWidth(shape.shapeSize);
            break;
        }

        glVertexPointer(shape.numOfPoints, GL_FLOAT, 0, shape.vertices);
        glColorPointer(3, GL_FLOAT, 0, shape.color);
        glDrawArrays(shape.drawType, 0, shape.numOfVertices);

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
    mtx_unlock(&shapesMutex);
}

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void controls(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS)
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
}