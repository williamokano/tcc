#include "../headers/graphics.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h> // for usleep
#endif

#define SHAPES_MAX_SIZE 30

thrd_t hiddenThread;
GLFWwindow* hiddenWindow = NULL;
Shape* shapes = NULL;
int numOfShapes = 0;

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

int hiddenMainLoop(void* args);
void drawBuffer();

void initWindow() {
    glfwSetErrorCallback(error_callback);
    /* Initialize the library */
    if (!glfwInit()) {
        fprintf(stderr, "Failed to init GLFW\n");
        exit(-1);
    } else {
        fprintf(stdout, "GLFW initialized\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    /* Create a windowed mode window and its OpenGL context */
    fprintf(stdout, "Attempting to create window\n");
    hiddenWindow = glfwCreateWindow(640, 480, "Window", NULL, NULL);
    if (!hiddenWindow) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        exit(-1);
    } else {
        fprintf(stdout, "Window created\n");
    }

    if (thrd_create(&hiddenThread, hiddenMainLoop, (void*)0) != thrd_success) {
        fprintf(stderr, "Failed to init hiddenMainLoop\n");
        exit(-1);
    } else {
        fprintf(stdout, "Window reported initalized\n");
    }

    shapes = malloc(SHAPES_MAX_SIZE * sizeof(Shape));
}

int isWindowInitialized() {
    return hiddenWindow != NULL;
}

void point(Point2D position, int size) {
    if (isWindowInitialized()) {
        Shape shape;

        shape.drawType = GL_POINTS;
        shape.shapeSize = size;

        shape.vertices = malloc(2 * sizeof(GLfloat));
        shape.vertices[0] = position.x;
        shape.vertices[1] = position.y;
        shape.numOfPoints = 2;

        shape.glSize = 1;

        shapes[numOfShapes++] = shape;
        printf("Shape added\n");
    }
}

void square(Point2D start, Point2D end) {
    if (isWindowInitialized()) {

    }
}

void sleep_cp(int time) {
    #ifdef WIN32
    Sleep(time);
    #else
    sleep(time);
    #endif
}

int hiddenMainLoop(void* args) {
    fprintf(stdout, "hiddenMainLoop started\n");

    /* Make the window's context current */
    glfwMakeContextCurrent(hiddenWindow);

    glViewport(0.0f, 0.0f, 640, 480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 640, 0, 480, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(hiddenWindow)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glEnableClientState(GL_VERTEX_ARRAY);

        drawBuffer();

        glDisableClientState(GL_VERTEX_ARRAY);

        /* Swap front and back buffers */
        glfwSwapBuffers(hiddenWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    exit(0);
}

void drawBuffer() {
    for (int i = 0; i < numOfShapes; i++) {
        Shape shape = shapes[i];

        glPointSize(shape.shapeSize);
        glVertexPointer(shape.numOfPoints, GL_FLOAT, 0, shape.vertices);
        glDrawArrays(shape.drawType, 0, shape.glSize);
    }
}
