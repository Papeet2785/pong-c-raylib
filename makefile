CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -O1 -I include

LIBGL_DIR = $(shell nix eval --raw nixpkgs#libGL.outPath)/lib
LIBX11_DIR = $(shell nix eval --raw nixpkgs#xorg.libX11.outPath)/lib

LDFLAGS = -L lib -L$(LIBGL_DIR) -L$(LIBX11_DIR)

LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = pong
SRC = main.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(TARGET)

.PHONY: clean
