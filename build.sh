#!/bin/bash

g++ -std=c++11 -c -shared ./src/utility.cpp -I./inc -o libutility.so -lsfml-system -lsfml-window -lsfml-graphics
g++ -std=c++11 ./src/main.cpp -I./inc -L. -lsfml-system -lsfml-window -lsfml-graphics -lutility
