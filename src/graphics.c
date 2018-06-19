#include "../headers/graphics.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h> // for usleep
#endif

#define SHAPES_MAX_SIZE 30
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

thrd_t hiddenThread;
mtx_t shapesMutex;
Point3D globalColor;
GLFWwindow* hiddenWindow = NULL;
Shape* shapes = NULL;
int numOfShapes = 0;

void error_callback(int error, const char* description);
void controls(GLFWwindow *window, int key, int scancode, int action, int mods);
int hiddenMainLoop(void* args);
void drawBuffer();

void initWindow() {
    if (thrd_create(&hiddenThread, hiddenMainLoop, (void*)0) != thrd_success) {
        fprintf(stderr, "Failed to init hiddenMainLoop\n");
        exit(-1);
    } else {
        fprintf(stdout, "Window reported initalized\n");
    }

    globalColor = point3d(0xFF, 0xFF, 0xFF);

    if (mtx_init(&shapesMutex, mtx_plain) != thrd_success) {
        fprintf(stderr, "Failed to create mutex\n");
        exit(-1);
    }

    mtx_lock(&shapesMutex);
    shapes = malloc(SHAPES_MAX_SIZE * sizeof(Shape));
    mtx_unlock(&shapesMutex);
}

int isWindowInitialized() {
    return hiddenWindow != NULL;
}

void clear() {
    mtx_lock(&shapesMutex);
    numOfShapes = 0;
    mtx_unlock(&shapesMutex);
}

void setColor(Point3D color) {
    globalColor = color;
}

Point3D getColor() {
    return globalColor;
}

void point(Point2D position, int size) {
    Shape shape;

    shape.drawType = GL_POINTS;
    shape.shapeSize = size;

    shape.vertices = malloc(2 * sizeof(GLfloat));
    shape.vertices[0] = position.x;
    shape.vertices[1] = position.y;
    shape.numOfPoints = 2;

    shape.color = malloc(6 * sizeof(GLfloat));

    // TODO add color mutex here
    shape.color[0] = getColor().x;
    shape.color[1] = getColor().y;
    shape.color[2] = getColor().z;

    shape.color[3] = getColor().x;
    shape.color[4] = getColor().y;
    shape.color[5] = getColor().z;

    shape.numOfVertices = 1;

    // Ensure no data race condition when adding new shapes because numOfShapes can be lost
    mtx_lock(&shapesMutex);
    shapes[numOfShapes++] = shape;
    mtx_unlock(&shapesMutex);
}

void square(Point2D start, Point2D end) {
    if (isWindowInitialized()) {

    }
}

void sleep_cp(int time) {
    #ifdef WIN32
    Sleep(time * 1000);
    #else
    sleep(time);
    #endif
}

int hiddenMainLoop(void* args) {
    fprintf(stdout, "hiddenMainLoop started\n");

    glfwSetErrorCallback(error_callback);
    /* Initialize the library */
    if (!glfwInit()) {
        fprintf(stderr, "Failed to init GLFW\n");
        exit(-1);
    } else {
        fprintf(stdout, "GLFW initialized\n");
    }

    /* Create a windowed mode window and its OpenGL context */
    fprintf(stdout, "Attempting to create window\n");
    hiddenWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window", NULL, NULL);
    if (!hiddenWindow) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        exit(-1);
    } else {
        fprintf(stdout, "Window created\n");
    }

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