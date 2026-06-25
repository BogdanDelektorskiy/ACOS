# Homework 4

## Task
A program that takes three command-line arguments:
- `argv[1]` – regular expression (POSIX extended)
- `argv[2]` – text
- `argv[3]` – replacement string

It finds all matches of the regex in the text, replaces them with the given replacement, stores the result in a dynamically allocated buffer (using `realloc` as needed), and prints the result.

## Compilation
```bash
make