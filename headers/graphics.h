#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <GLFW/glfw3.h>
#include "tinycthread.h"
#include "point.h"
#include "shape.h"

void initWindow();
int isWindowInitialized();
void clear();

// Color stuff
void setColor(Point3D color);
Point3D getColor();

void point(Point2D position, int size);
void triangle(Point2D p1, Point2D p2, Point2D p3);
void square(Point2D start, Point2D end);
void sleep_cp(int time);

#endif // GRAPHICS_H_INCLUDED
