CFLAGS = -lSDL2_ttf -lSDL2 -lSDL2main -Wall -Wextra -pedantic -std=gnu17

compile: ./src/*.c
	$(CC) ./src/*.c -o sav $(CFLAGS)