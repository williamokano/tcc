#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED
#include <GLFW/glfw3.h>

typedef struct Shape {
    GLfloat *vertices;
    int shapeSize;
    int numOfPoints;
    unsigned char drawType;
    int numOfVertices;
    GLfloat *color;
} Shape;

#endif // SHAPE_H_INCLUDED
