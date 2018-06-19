#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "headers/graphics.h"

int main() {
    initWindow();

    while(true) {
        printf("Entering sleep mode...\n");
        sleep(1);
    }
    return 0;
}
