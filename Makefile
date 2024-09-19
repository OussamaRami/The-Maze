CC = gcc
CFLAGS = -I src/include -L src/lib
LIBS = -lmingw32 -lSDL2main -lSDL2_image -lSDL2 -lm

all: maze_game

maze_game: main.o player.o game.o render.o
	$(CC) -o maze_game main.o player.o game.o render.o $(CFLAGS) $(LIBS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

player.o: player.c
	$(CC) -c player.c $(CFLAGS)

game.o: game.c
	$(CC) -c game.c $(CFLAGS)

render.o: render.c
	$(CC) -c render.c $(CFLAGS)

clean:
	rm -f *.o maze_game
