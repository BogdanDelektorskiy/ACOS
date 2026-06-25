# Homework 2

## Tasks

### 1. Print N lines from file starting at line I (task1.c)
- Usage: `./task1 <filename> <I> <N>`
- Based on open/close/read/write.
- Reads file in 4096-byte blocks, counts lines, outputs the requested range.
- Buffered write to minimize system calls.

### 2. Print the middle line of a text file (task2.c)
- Usage: `./task2 <filename>`
- Uses lseek to skip the first half.
- Determines the line containing the byte at position file_size/2 and prints it entirely.

## Compilation
```bash
make