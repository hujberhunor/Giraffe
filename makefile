
CC = gcc
CFLAGS = -Wall -g
LIBS = -lm -lncurses

SRCS = mainUI.c audio.c files.c tui.c
OBJS = $(SRCS:.c=.o)
TARGET = mainUI

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean run

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
