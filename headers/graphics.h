#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <GLFW/glfw3.h>
#include "tinycthread.h"
#include "point.h"
#include "shape.h"

void initWindow();
int isWindowInitialized();
void point(Point2D position, int size);
void square(Point2D start, Point2D end);
void sleep_cp(int time);

#endif // GRAPHICS_H_INCLUDED
