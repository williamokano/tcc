#!/bin/bash

ENTRYPOINT=${1:-main}
OUTPUT_FILE="bin/$ENTRYPOINT"

# Create bin folder if not found
if [ ! -d "./bin" ];then
    mkdir -p ./bin
fi

# Clean bin folder if present
if [ -f "./$OUTPUT_FILE" ];then
    rm "./$OUTPUT_FILE"
fi

gcc -o "$OUTPUT_FILE" "$ENTRYPOINT.c" \
    src/graphics.c \
    src/point.c \
    src/tinycthread.c \
    -lGL -lX11 -lpthread -lglfw

if [ $? -gt 0 ];then
    echo "Failed to compile"
    exit $?;
else
    echo "compiled."
    echo "To execute just type: ./$OUTPUT_FILE"
fi