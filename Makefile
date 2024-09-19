# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -g
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image
OBJS = main.o game.o player.o render.o

# Target executable
TARGET = maze_game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(SDL_LDFLAGS)

main.o: main.c game.h player.h render.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c main.c

game.o: game.c game.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c game.c

player.o: player.c player.h game.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c player.c

render.o: render.c render.h game.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c render.c

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
