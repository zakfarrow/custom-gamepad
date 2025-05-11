CC = gcc
TARGET = build/main
SRC = main.c
CFLAGS = -Wall -Wextra
LIBS = -lwiringPi -lads7830 -lraylib

all: $(TARGET)

$(TARGET): $(SRC) | build
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LIBS)

build:
	mkdir -p build

clean:
	rm -rf build

run:
	LIBGL_ALWAYS_SOFTWARE=1 $(TARGET)

.PHONY: all clean run 
