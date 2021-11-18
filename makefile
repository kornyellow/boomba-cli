all: main.cpp
	g++ -Wall -pedantic main.cpp -lncurses -lSDL_mixer -o main `sdl-config --libs`

clean:
	rm main
