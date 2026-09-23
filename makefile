CC = clang

WAYLAND = $(shell nix eval --raw nixpkgs#wayland.outPath)
XKBCOMMON = $(shell nix eval --raw nixpkgs#libxkbcommon.outPath)
LIBGL = $(shell nix eval --raw nixpkgs#libGL.outPath)

CFLAGS = -Wall -Wextra -std=c99 -O1 -I include
LDFLAGS = -L lib -L $(WAYLAND)/lib -L $(XKBCOMMON)/lib -L $(LIBGL)/lib -lraylib -lm -lwayland-client -lwayland-cursor -lwayland-egl -lxkbcommon -lGL -lpthread -ldl -lrt

TARGET = pong.out
SRC = main.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
