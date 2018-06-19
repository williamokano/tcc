#include "../headers/graphics.h"
#include <stdio.h>
#include <stdlib.h>

thrd_t hiddenThread;
GLFWwindow* hiddenWindow;

void hiddenMainLoop(void* args);

void initWindow() {
    if (thrd_create(&hiddenThread, hiddenMainLoop, (void*)0) != thrd_success) {
        fprintf(stderr, "Failed to init hiddenMainLoop\n");
        exit(-1);
    }
}

void hiddenMainLoop(void* args) {
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    hiddenWindow = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!hiddenWindow) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(hiddenWindow);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(hiddenWindow)) {
        printf("Hello\n");
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(hiddenWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    exit(-1);
}
