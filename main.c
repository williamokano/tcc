#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "headers/graphics.h"

int main() {
    initWindow();
    int columnOffset = 0;
    
    setColor(point3d(0xFF, 0x00, 0xFF));
    triangle(
        point2d(100, 100), 
        point2d(200, 200), 
        point2d(200, 100)
    );

    setColor(point3d(0x00, 0xFF, 0xFF));
    point(point2d(500, 500), 50);

    while(true) {
        // clear();
        // point(point2d(columnOffset, columnOffset), 50);
        // columnOffset += 20;
        sleep_cp(2);
    }
    return 0;
}
