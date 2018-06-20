#include <stdio.h>
#include <stdlib.h>
#include "headers/graphics.h"

int main() {
    initWindow();
    
    setColor(point3d(0xFF, 0x00, 0xFF));

    point(point2d(100, 100), 30);
    point(point2d(300, 300), 50);
    
    triangle(
        point2d(100, 100),
        point2d(200, 200),
        point2d(200, 100)
    );

    getchar();
    return 0;
}
