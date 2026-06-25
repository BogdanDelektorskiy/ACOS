CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -Wl,--wrap,fred -Wl,--wrap,john

all: main libinterpose.so

main: main.o fred_int.o john_int.o bill.o sam.o
	$(CC) $(CFLAGS) -o main main.o fred_int.o john_int.o bill.o sam.o

libinterpose.so: bill_int.o sam_int.o
	$(CC) -shared -o libinterpose.so bill_int.o sam_int.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

fred_int.o: fred_int.c
	$(CC) $(CFLAGS) -c fred_int.c

john_int.o: john_int.c
	$(CC) $(CFLAGS) -c john_int.c

bill_int.o: bill_int.c
	$(CC) $(CFLAGS) -fPIC -c bill_int.c

sam_int.o: sam_int.c
	$(CC) $(CFLAGS) -fPIC -c sam_int.c

bill.o: bill.c
	$(CC) $(CFLAGS) -c bill.c

sam.o: sam.c
	$(CC) $(CFLAGS) -c sam.c

clean:
	rm -f *.o main libinterpose.so