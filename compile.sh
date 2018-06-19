#!/bin/bash

gcc -o bin/main main.c src/graphics.c src/point.c src/tinycthread.c -lGL -lX11 -lpthread -lglfw