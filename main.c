#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "headers/graphics.h"

int main() {
    initWindow();

    point(point2d(100, 200), 50);

    point(point2d(350, 400), 25);

    while(true) {
        printf("Entering sleep mode...\n");
        sleep_cp(1);
    }
    return 0;
}
