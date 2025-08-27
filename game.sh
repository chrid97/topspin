#!/bin/bash

if [[ "$OSTYPE" == "darwin"* ]]; then
  # macOS settings
  eval cc ./src/main.c $(pkg-config --libs --cflags raylib) -o topspin.exe
else
  # Linux settings
  gcc ./src/main.c \
    -I./lib/raylib/include \
    -L./lib/raylib/lib -Wl,-rpath=./lib/raylib/lib \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 \
    -o topspin.exe
fi

./topspin.exe
rm ./topspin.exe
