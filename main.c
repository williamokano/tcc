#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "headers/graphics.h"

int main() {
    initWindow();
    int columnOffset = 0;
    
    setColor(point3d(0xFF, 0x00, 0x00));

    while(true) {
        clear();
        point(point2d(columnOffset, columnOffset), 50);
        columnOffset += 20;
        sleep_cp(2);
    }
    return 0;
}
