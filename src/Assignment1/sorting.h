#ifndef _SORTING_H_

#define _SORTING_H_

#include "structs.h"



void quickSort_Serial(struct indist *left, struct indist *right);

void mergeSort_Serial(struct indist **importList, int left, int right, int points);

void bubbleSort_Serial(struct indist **importList, int points);

#endif