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

Shape createShape(
    unsigned char drawType,
    int numOfVertices,
    GLfloat *vertices,
    int shapeSize,
    int numOfPoints,
    GLfloat *color
);

GLfloat* shapeColor(int numOfVertices, int red, int green, int blue);

#endif // SHAPE_H_INCLUDED
