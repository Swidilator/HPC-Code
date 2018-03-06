#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include "dataGen.h"
#include "kClosestPoints.h"
#include "structs.h"



int main(void)
{
    //omp_set_num_threads(8);
    srand(time(NULL));
    double **dataSet = makeDataset(DIM, POINTS, MIN, MAX);

    double **input = makeDataset(DIM, Q, MIN, MAX);

    struct report **reports = malloc(Q * sizeof(struct report *));

    struct report *totalReport = malloc(sizeof(struct report *));
    //#pragma omp parallel for
    for (int i = 0; i < Q; i++)
    {
        reports[i] = kClosestPoints_Serial(input[i], dataSet, K, DIM, POINTS, &euclideanDistance, SORT_FUNC);
        //printf("%d:\tsorting: %f\tdistance: %f\n", i, reports[i]->sorting, reports[i]->distance);
        totalReport->sorting += reports[i]->sorting;
        totalReport->distance += reports[i]->distance;
    }

    printf("Total:\tsorting: %f\tdistance: %f\n", totalReport->sorting, totalReport->distance);

    return (EXIT_SUCCESS);
}