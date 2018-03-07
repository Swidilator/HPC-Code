#ifndef _KCLOSESTPOINTS_H_

#define _KCLOSESTPOINTS_H_

#include "structs.h"

struct report *kClosestPoints_Serial(double *input, double **dataSet, int k, int dim, int points, int distanceFunc, int sortingFunc, int PAR, int TASKS);

double manhattanDistance(double *point1, double *point2, int dim);

double euclideanDistance(double *point1, double *point2, int dim);

void manhattanDistance_Serial(double *input, double **dataSet, struct indist **distanceList, int points, int dim);

void manhattanDistance_Parallel(double *input, double **dataSet, struct indist **distanceList, int points, int dim);

void euclidianDistance_Serial(double *input, double **dataSet, struct indist **distanceList, int points, int dim);

void euclidianDistance_Parallel(double *input, double **dataSet, struct indist **distanceList, int points, int dim);

#endif