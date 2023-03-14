CC := gcc
SOURCES := $(wildcard src/*.c)
OUT_NAME := min_SDL_app

all: 
	${CC} ${SOURCES} -I/usr/local/include -L/usr/local/lib -lSDL2 -o ${OUT_NAME}

clean:
	rm src/*.gch

.PHONY: clean
