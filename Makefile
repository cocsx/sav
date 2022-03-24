CFLAGS = -lSDL2 -lSDL2main -Wall -Wextra -pedantic -std=c17

compile: ./src/*.c
	$(CC) ./src/*.c -o sav $(CFLAGS)