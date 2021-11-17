all: main.cpp
	g++ main.cpp -lncurses -o main

clean:
	rm main
