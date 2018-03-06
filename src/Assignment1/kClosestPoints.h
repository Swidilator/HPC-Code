#ifndef _KCLOSESTPOINTS_H_

#define _KCLOSESTPOINTS_H_

#include "structs.h"


struct report *kClosestPoints_Serial(double *input, double **dataSet, int k, int dim, int points, double (*distanceFunc)(double *, double *, int), int sortingFunc);

double manhattanDistance(double *point1, double *point2, int dim);

double euclideanDistance(double *point1, double *point2, int dim);

#endif