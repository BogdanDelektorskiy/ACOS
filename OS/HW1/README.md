# Homework 1 – C programming basics

## Tasks

### 1. Swap two integers (`task1.c`)
Write a program in C that:
- inputs two integer values `x` and `y`;
- calls a function `swap` that takes the values as arguments and swaps them;
- prints the values after the swap.

### 2. Dynamic array reversal (`task2.c`)
Write a program in C that:
- inputs an integer value `N`;
- allocates an array of `N` integer elements (using `malloc`);
- fills the array with integer values from standard input;
- reverses the array;
- prints the resulting array;
- deallocates the array (using `free`).

### 3. Matrix transposition (`task3.c`)
Write a program in C that:
- inputs two integer values `N` and `M`;
- allocates a matrix of size `N * M` and fills it with values from standard input;
- transposes the matrix;
- prints the resulting matrix;
- deallocates the matrices.
*Note:* use `malloc` and `free` for memory management.

### 4. Singly-linked list reversal (`task4.c`)
Write a program in C that:
- creates a singly-linked list;
- adds numbers from standard input to the list until the user inputs `0`;
- reverses the list;
- prints the resulting list;
- deallocates the list.
*Note:* use `malloc` and `free` for list entries.

## Compilation

All programs can be built at once using the provided `Makefile`:

```bash
make          # build all
./task1       # run a specific program
make clean    # remove all executables