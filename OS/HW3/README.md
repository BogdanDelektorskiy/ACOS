# Homework 3

## Task
Improve Task 1 from Part 1 with interpositioning:
- Link-time interpositioning for `fred` and `john`.
- Load-time interpositioning for `bill` and `sam`.
- Interposed functions print a message like `"fred is called"`.

## Files
- `main.c` – calls `fred()`, `john()`, `bill()`, `sam()`.
- `fred.c`, `john.c`, `bill.c`, `sam.c` – original implementations (print "original ...").
- `fred_int.c`, `john_int.c` – replacement functions for link-time interpositioning.
- `bill_int.c`, `sam_int.c` – replacement functions for load-time interpositioning (shared library).

## Compilation and Usage
```bash
make
./main                          # fred and john are intercepted at link time
LD_PRELOAD=./libinterpose.so ./main   # bill and sam are intercepted at load time