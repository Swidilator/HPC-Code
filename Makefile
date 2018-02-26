CC=gcc
CFLAGS= -Wall -fopenmp

all: ex1

ex1 : 
	$(CC) $(CFLAGS) $@.c -o $@.out

clean:
	rm -f *.out *.o