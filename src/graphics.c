#include "../headers/graphics.h"
#include <stdio.h>
#include <stdlib.h>

#define SHAPES_MAX_SIZE 100
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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

Shape* shapes = NULL;
int numOfShapes = 0;

int vermelhoGlobal = 255;
int verdeGlobal = 255;
int azulGlobal = 255;

int tamanhoGlobal = 1;
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
    mtx_unlock(&shapesMutex);
}

void limparFormas() {
    mtx_lock(&shapesMutex);
    numOfShapes = 0;
    mtx_unlock(&shapesMutex);
}

void inicializarBiblioteca() {
    if (thrd_create(&hiddenThread, hiddenMainLoop, (void*)0) != thrd_success) {
        fprintf(stderr, "Falha ao inicializar hiddenMainLoop\n");
        exit(-1);
    }
    #ifdef DEBUG
    else {
        fprintf(stdout, "Window reported initalized\n");
    }
    #endif

    definirCor(255, 255, 255); // RGB(255, 255, 255) = Branco

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


// Drawing stuff
void poligono(int numeroDeVertices, GLfloat* posicoes) {

}

void ponto(int posX, int posY) {
    Shape shape;

    shape.drawType = GL_POINTS;
    shape.shapeSize = obterTamanho();

    shape.vertices = malloc(2 * sizeof(GLfloat));
    shape.vertices[0] = posX;
    shape.vertices[1] = posY;
    shape.numOfPoints = 2;
    shape.numOfVertices = 1;

    shape.color = malloc(shape.numOfVertices * sizeof(GLfloat) * 3);

    for (int i = 0; i < shape.numOfVertices; i++) {
    // TODO add color mutex here
        shape.color[3 * i + 0] = vermelhoGlobal;
        shape.color[3 * i + 1] = verdeGlobal;
        shape.color[3 * i + 2] = azulGlobal;
    }

    addShape(shape);
}

void triangulo(Point2D p1, Point2D p2, Point2D p3) {
    Shape shape;

    shape.drawType = GL_TRIANGLES;
    shape.numOfPoints = 2;
    shape.numOfVertices = 3;

    shape.vertices = malloc(shape.numOfVertices * sizeof(GLfloat) * 2);
    shape.vertices[0] = p1.x;
    shape.vertices[1] = p1.y;

    shape.vertices[2] = p2.x;
    shape.vertices[3] = p2.y;

    shape.vertices[4] = p3.x;
    shape.vertices[5] = p3.y;

    shape.color = malloc(shape.numOfVertices * sizeof(GLfloat) * 3);

    for (int i = 0; i <= shape.numOfVertices; i++) {
    // TODO add color mutex here
        shape.color[3 * i + 0] = vermelhoGlobal;
        shape.color[3 * i + 1] = verdeGlobal;
        shape.color[3 * i + 2] = azulGlobal;
    }

    addShape(shape);
}

void retangulo(int posX, int posY, int width, int height) {
    Shape shape;

    shape.drawType = GL_QUADS;
    shape.numOfPoints = 2;
    shape.numOfVertices = 4;

    shape.vertices = malloc(2 * shape.numOfVertices * sizeof(GLfloat));
    shape.vertices[0] = posX;
    shape.vertices[1] = posY;
    
    shape.vertices[2] = posX + width;
    shape.vertices[3] = posY;

    shape.vertices[4] = posX + width;
    shape.vertices[5] = posY + height;

    shape.vertices[6] = posX;
    shape.vertices[7] = posY + height;

    shape.color = malloc(3 * shape.numOfVertices * sizeof(GLfloat));

    for (int i = 0; i < shape.numOfVertices; i++) {
    // TODO add color mutex here
        shape.color[3 * i + 0] = vermelhoGlobal;
        shape.color[3 * i + 1] = verdeGlobal;
        shape.color[3 * i + 2] = azulGlobal;
    }

    addShape(shape);
}

void quadrado(int posX, int posY, int tamanhoLado) {
    retangulo(posX, posY, tamanhoLado, tamanhoLado);
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

    hiddenWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window", NULL, NULL);
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

    glViewport(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, 0, 1);
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

        glPointSize(shape.shapeSize);
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