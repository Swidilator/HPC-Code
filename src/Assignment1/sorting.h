#ifndef _SORTING_H_

#define _SORTING_H_

#include "structs.h"



void quickSort_Serial(struct indist **importList, int left, int right, int points);

void mergeSort_Serial(struct indist **importList, int left, int right, int points);

void bubbleSort_Serial(struct indist **importList, int points);

void quickSort_Parallel_Sections(struct indist **importList, int left, int right, int points, int pointsTotal);

void mergeSort_Parallel_Sections(struct indist **importList, int left, int right, int points, int pointsTotal);

void quickSort_Parallel_Tasks(struct indist **importList, int left, int right, int points, int pointsTotal);

void mergeSort_Parallel_Tasks(struct indist **importList, int left, int right, int points, int pointsTotal);

void bubbleSort_Parallel(struct indist **importList, int points);

#endif