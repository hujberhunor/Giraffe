
# Makefile

CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lm
SOURCES = main.c audio.c fileMan.c
TARGET = main

all: $(TARGET)

$(TARGET): $(SOURCES)
		$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SOURCES)

run: all
		./$(TARGET)

clean:
		rm -f $(TARGET)

.PHONY: all run clean
