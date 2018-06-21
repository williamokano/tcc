#!/bin/bash


# Create bin folder if not found
if [ ! -d "./bin" ];then
    mkdir -p ./bin
fi

# Clean bin folder if present
if [ -f "./bin/main" ];then
    rm ./bin/main
fi

gcc -o bin/main main.c \
    src/graphics.c \
    src/point.c \
    src/tinycthread.c \
    -lGL -lX11 -lpthread -lglfw