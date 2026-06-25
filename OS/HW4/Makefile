CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = task

all: $(TARGET)

$(TARGET): task.c
	$(CC) $(CFLAGS) -o $(TARGET) task.c

clean:
	rm -f $(TARGET)