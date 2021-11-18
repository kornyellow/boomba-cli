all: main.cpp
	g++ -Wall -pedantic main.cpp -lncurses -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lSDL_mixer -o main `sdl-config --libs`

clean:
	rm main
