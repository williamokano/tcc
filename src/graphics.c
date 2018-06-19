#include "../headers/graphics.h"
#include <stdio.h>

thrd_t hiddenThread;

void sayHello() {
    printf("Say hello from thread\n");
    printf("Say hello from thread again!!!\n");
}

void saySomethingImGivingUpOnYou() {
    if (thrd_create(&hiddenThread, sayHello, (void*)0) == thrd_success) {
        printf("Running\n");
    }
}
