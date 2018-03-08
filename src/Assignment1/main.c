#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include "dataGen.h"
#include "kClosestPoints.h"
#include "structs.h"

int DIM = 32;

int MIN = -100;
int MAX = 100;


//int POINTS = 50000;
int K = 5;
//int QUERY = 1;



//int nArray[4] = {1, 5, 10, 15};int nSize = 4;
int nArray[1] = {3}; int nSize = 1;


//int mArray[4] = {10000, 50000, 100000, 200000}; int mSize = 4;
int mArray[1] = {200000}; int mSize = 1;


int dArray[4] = {3, 30, 300, 3000}; int dSize = 4;
//int dArray[1] = {30}; int dSize = 1;


int SORT_FUNC = 0; //0: Quicksort      1: Mergesort    2: Bubblesort
int DIST_FUNC = 0; //0: Euclidian     1: Manhattan
int PAR = 0;
int TASKS = 0;

int main(void)
{
    omp_set_num_threads(8);
    srand(time(NULL));

    printf("\n\nParallel: %d  Tasks: %d  Sort: %d  Dist: %d\n", PAR, TASKS, SORT_FUNC, DIST_FUNC);

    for (int k = 0; k < dSize; k++)
    {
        for (int i = 0; i < mSize; i++)
        {
            double **dataSet = makeDataset(dArray[k], mArray[i], MIN, MAX);
            for (int j = 0; j < nSize; j++)
            {
                double **input = makeDataset(dArray[k], nArray[j], MIN, MAX);

                struct report **reports = malloc(nArray[j] * sizeof(struct report *));

                struct report *totalReport = malloc(sizeof(struct report *));
                totalReport->distance = 0;
                totalReport->sorting = 0;

                //#pragma omp parallel for

                //struct report *kClosestPoints_Serial(double *input, double **dataSet, int k, int dim, int points, int distanceFunc, int sortingFunc, int PAR, int TASKS);
                //#pragma omp parallel
                for(int f = 0; f < nArray[j]; f++){
                    reports[f] = kClosestPoints_Serial(input[f], dataSet, K, dArray[k], mArray[i], DIST_FUNC, SORT_FUNC, PAR, TASKS);
                    //printf("%d:\tsorting: %f\tdistance: %f\n", i, reports[i]->sorting, reports[i]->distance);
                    totalReport->sorting += reports[f]->sorting;
                    totalReport->distance += reports[f]->distance;
                }

                //printf("m: %d\t\tn: %d\t\td: %d\n", mArray[i], QUERY, dArray[k]);
                //printf("Total:\tsorting: %f\tdistance: %f\n", totalReport->sorting, totalReport->distance);

                printf("m: %d\t\tn: %d\t\td: %d\n", mArray[i], nArray[j], dArray[k]);
                double totTime = totalReport->sorting + totalReport->distance;
                printf("Total: %f\tsorting: %f\tdistance: %f\n",totTime, totalReport->sorting/totTime, totalReport->distance/totTime);


                for(int a = 0; a < nArray[j]; a++){
                    free(input[a]);
                    free(reports[a]);
                }

                free(totalReport);
                free(reports);
            }
        }
    }
    printf("\n");
    return (EXIT_SUCCESS);
}