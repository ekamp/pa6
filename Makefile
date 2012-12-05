CC = gcc
CFLAGS  = -ansi -pedantic -Wall -Wextra -O -g

bookOrders: bookOrders.h bookOrders.c libdatstr.a
	$(CC) $(CFLAGS) -o bookOrders bookOrders.c

libdatstr.a: helper.o
	ar rcs libdatstr.a helper.o

helper.o: helper.h helper.c
	$(CC) $(CFLAGS) -c helper.c

clean:
	rm -f bookOrders *~ a.out *.o 
