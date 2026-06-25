# Homework 6 – Shell scripts: read & sum

## 1. `c8.sh` — Welcome script

**Research:**
- `read` exit status: 0 if a line is read (even empty), non‑zero (1) on EOF.
  (Check with `help read` — it's a shell builtin.)
- Suppress trailing newline after `echo`: use `echo -n "text"` or `printf "%s" "text"`.

**Script behaviour:**
- Asks for a name.
- If the input is empty (just Enter), uses `"tmpuser"`.
- Prints `Hello, <name>!`
