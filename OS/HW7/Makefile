CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -pthread

all: task

task: task.c
	$(CC) $(CFLAGS) -o task task.c $(LDFLAGS)

clean:
	rm -f task
	