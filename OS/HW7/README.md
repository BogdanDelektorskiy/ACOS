# Homework 7 – Multithreaded array sum

## Task
- Input integer N (>= 16).
- Allocate array of N random integers.
- Split the array into 4 approximately equal parts.
- Create 4 threads, each computes the sum of its part and adds the result to a global variable `global_sum` protected by a mutex.
- Main thread prints the array, waits for all threads to finish, and prints the total sum.
