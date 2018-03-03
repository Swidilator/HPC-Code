CC=gcc
CFLAGS= -Wall -fopenmp -lm -g3 -O0

all: clean ex1 assignment

ex1 : 
	$(CC) $(CFLAGS) src/$@.c -o $@.out

assignment : 
	$(CC) $(CFLAGS) src/Assignment1/main.c src/Assignment1/dataGen.c src/Assignment1/sorting.c src/Assignment1/kClosestPoints.c -o $@.out

clean:
	rm -f *.out *.o