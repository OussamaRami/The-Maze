all:
	gcc -I src/include -L src/lib -o maze game.c maze.c render.c player.c -lmingw32 -lSDL2main -lSDL2_image -lSDL2 -lm
