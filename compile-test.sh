#!/bin/bash

gcc -o bin/test test.c src/graphics.c src/point.c src/tinycthread.c -lGL -lX11 -lpthread -lglfw