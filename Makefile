FLAGS = -lSDL2_ttf -lSDL2 -lSDL2main -Wall -Wextra -pedantic -std=gnu17

all: compile
	./build/sav

compile: ./src/*.c
	mkdir -p ./build
	$(CC) ./src/*.c -o ./build/sav $(FLAGS)

clean: 
	rm -rf build/
