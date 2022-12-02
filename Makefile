CC = gcc
CFLAGS = -Wall
TARGET = main

all: $(TARGET).c
	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET)

clean:
	$(RM) $(TARGET)
