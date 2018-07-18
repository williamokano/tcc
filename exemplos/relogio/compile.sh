#!/bin/bash

gcc -o relogio.exe main.c -I./headers -L. -lgraphics -lGL -lX11 -lpthread -lglfw -lm