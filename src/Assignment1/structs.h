#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#define DIM 500

#define MIN -100
#define MAX 100

#define SORT_FUNC 0     //0: Quicksort      1: Mergesort    2: Bubblesort

#define POINTS 1000000
#define K 5
#define Q 10


#define PAR 1
#define TASKS 1

struct indist
{
    int index;
    double dist;
};

struct report
{
    double sorting;
    double distance;
};

#endif