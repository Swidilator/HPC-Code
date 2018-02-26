CC=gcc
CFLAGS=-c -Wall -fopenmp

all: ex1

ex1 : 
	$(CC) $(CFLAGS) $@.c -o $@.out