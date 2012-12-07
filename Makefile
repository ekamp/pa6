CC = gcc
CFLAGS  = -ansi -pedantic -Wall -Wextra -O -g

bookOrders: bookOrders.h bookOrders.c libdatstr.a
	$(CC) $(CFLAGS) bookOrders.c -L. -l pthread -l datstr -o bookOrders

libdatstr.a: datstr.o
	ar rcs libdatstr.a datstr.o

datstr.o: datstr.h datstr.c
	$(CC) $(CFLAGS) datstr.c -l pthread -c

clean:
	rm -f bookOrders *~ a.out *.o libdatstr.a
