#!/bin/bash

OUTPUT_FILE="bin/$ENTRYPOINT"

# Create bin folder if not found
if [ ! -d "./bin" ];then
    mkdir -p ./bin
fi

# Clean bin folder if present
if [ -f "./graphics.o" ];then
    rm "./graphics.o"
fi

# Clean bin folder if present
if [ -f "./tinycthread.o" ];then
    rm "./tinycthread.o"
fi

# Clean bin folder if present
if [ -f "./shape.o" ];then
    rm "./shape.o"
fi

gcc -c -o "./bin/graphics.o" src/graphics.c
gcc -c -o "./bin/tinycthread.o" src/tinycthread.c
gcc -c -o "./bin/shape.o" src/shape.c

#    src/tinycthread.c \
#    src/shape.c \
#    -lGL -lX11 -lpthread -lglfw -lm

if [ $? -gt 0 ];then
    echo "Failed to compile"
    exit $?;
else
    echo "compiled."
fi