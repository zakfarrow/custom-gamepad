CC = gcc
TARGET = build/main
SRC = main.c
CFLAGS = -Wall -Wextra
LIBS = -lwiringPi -lads7830 -lraylib

PI_HOST = pi
PI_DIR = /home/zakfarrow/projects/custom-gamepad

all: $(TARGET)

$(TARGET): $(SRC) | build
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LIBS)

deploy:
	ssh $(PI_HOST) "mkdir -p $(PI_DIR)"
	rsync -avz --exclude=*.o ./* $(PI_HOST):$(PI_DIR)/
	ssh $(PI_HOST) "cd $(PI_DIR) && make"

build:
	mkdir -p build

clean:
	rm -rf build

remote-run:
	ssh $(PI_HOST) "cd $(PI_DIR) && make run"

remote-clean:
	ssh $(PI_HOST) "cd $(PI_DIR) && rm -rf build"

run:
	LIBGL_ALWAYS_SOFTWARE=1 $(TARGET)

.PHONY: all deploy clean run remote-run rmeote-clean
