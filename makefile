CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -O1 -I include

LDFLAGS = -L lib -lraylib -lopengl32 -lgdi32 -lwinmm

TARGET = pong.exe

SRC = main.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	del /Q $(TARGET) 2>NUL