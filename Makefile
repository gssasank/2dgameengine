SLD2FLAGS = $(shell pkg-config --cflags --libs sdl2)
SDL2MIXERFLAGS = $(shell pkg-config --cflags --libs sdl2_mixer)
SDL2IMAGEFLAGS = $(shell pkg-config --cflags --libs sdl2_image) 
SDL2TTFFLAGS = $(shell pkg-config --cflags --libs sdl2_ttf)

build:
	g++ -Wall -std=c++17 src/*.cpp $(SLD2FLAGS) $(SDL2IMAGEFLAGS) $(SDL2MIXERFLAGS) $(SDL2TTFFLAGS) -llua -o gameengine

run:
	./gameengine

clean:
	rm gameengine
