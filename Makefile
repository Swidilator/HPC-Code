CC=gcc
CFLAGS= -Wall -fopenmp -lm -g3

all: clean ex1 assignment

ex1 : 
	$(CC) $(CFLAGS) src/$@.c -o $@.out

assignment : 
	$(CC) $(CFLAGS) src/Assignment1/main.c -o $@.out

clean:
	rm -f *.out *.o