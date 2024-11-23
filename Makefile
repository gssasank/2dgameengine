# Basic flags
CC = g++
CFLAGS = -Wall -Wfatal-errors
CSTD = -std=c++2b
SRCFILES =  ./src/*.cpp \
			./src/Game/*.cpp \
			./src/Logger/*.cpp \
			./src/ECS/*.cpp

# Base SDL2 flags
SDL2FLAGS = $(shell pkg-config --cflags sdl2)
SDL2LIBS = $(shell pkg-config --libs sdl2)

# Additional SDL2 module flags (without base SDL2)
SDL2MIXERFLAGS = $(shell pkg-config --cflags sdl2_mixer)
SDL2MIXERLIBS = -lSDL2_mixer

SDL2IMAGEFLAGS = $(shell pkg-config --cflags sdl2_image)
SDL2IMAGELIBS = -lSDL2_image

SDL2TTFFLAGS = $(shell pkg-config --cflags sdl2_ttf)
SDL2TTFLIBS = -lSDL2_ttf

OBJECT = gameengine

CFLAGS = $(SDL2FLAGS) $(SDL2MIXERFLAGS) $(SDL2IMAGEFLAGS) $(SDL2TTFFLAGS)
LIBS = $(SDL2LIBS) $(SDL2MIXERLIBS) $(SDL2IMAGELIBS) $(SDL2TTFLIBS) -llua -I"./libs/"

#-------------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------------------

build:
	$(CC) $(CFLAGS) $(CSTD) $(SRCFILES) $(CFLAGS) $(LIBS) -o $(OBJECT)

run:
	./$(OBJECT)

clean:
	rm $(OBJECT)

all: build run