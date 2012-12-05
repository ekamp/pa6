CC = gcc
CFLAGS  = -ansi -pedantic -Wall -Wextra -O -g

bookOrders: bookOrders.h bookOrders.c libdatstr.a
	$(CC) $(CFLAGS) -o bookOrders bookOrders.c

libdatstr.a: datstr.o
	ar rcs libdatstr.a helper.o

helper.o: datstr.h datstr.c
	$(CC) $(CFLAGS) -c datstr.c

clean:
	rm -f bookOrders *~ a.out *.o 
