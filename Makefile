build:
	g++ -Wall -std=c++17 src/*.cpp $(shell pkg-config --cflags --libs sdl2) -o gameengine
run:
	./gameengine

clean:
	rm gameengine
