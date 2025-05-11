CC = gcc
TARGET = build/main
SRC = main.c
CFLAGS = -Wall -Wextra
LIBS = -lwiringPi -lads7830 -lraylib

PI_USER = pi
PI_HOST =
PI_DIR = /home/zakfarrow/projects/custom-gamepad

all: $(TARGET)

$(TARGET): $(SRC) | build
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LIBS)

deploy:
	ssh $(PI_USER)@$(PI_HOST) "mkdir -p $(PI_DIR)"
	rsync -avz --exclude=*.o ./* $(PI_USER)@$(PI_HOST):$(PI_DIR)/
	ssh $(PI_USER)@$(PI_HOST) "cd $(PI_DIR) && make"

build:
	mkdir -p build

clean:
	rm -rf build

remote-run:
	ssh $(PI_USER)@$(PI_HOST) "cd $(PI_DIR) && make run"

run:
	LIBGL_ALWAYS_SOFTWARE=1 $(TARGET)

.PHONY: all deploy clean run remote-run
