#include <stdlib.h>
#include "../headers/shape.h"

// Função facilitadora que age como se fosse um método construtor
Shape createShape(
    unsigned char drawType,
    int numOfVertices,
    GLfloat *vertices,
    int shapeSize,
    int numOfPoints,
    GLfloat *color
) {
    Shape s;

    s.vertices = vertices;
    s.shapeSize = shapeSize;
    s.numOfPoints = numOfPoints;
    s.drawType = drawType;
    s.numOfVertices = numOfVertices;
    s.color = color;

    return s;
}

GLfloat* shapeColor(int numOfVertices, int red, int green, int blue) {
    GLfloat* color = malloc(numOfVertices * sizeof(GLfloat) * 3);

    for (int i = 0; i < numOfVertices; i++) {
        color[3 * i + 0] = red;
        color[3 * i + 1] = green;
        color[3 * i + 2] = blue;
    }

    return color;
}