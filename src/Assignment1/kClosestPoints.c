#include "kClosestPoints.h"
#include "sorting.h"
#include "structs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <omp.h>

//Serial version of K Closest Points algorithm
struct report *kClosestPoints_Serial(double *input, double **dataSet, int k, int dim, int points, int distanceFunc, int sortingFunc, int par, int TASKS)
{
    struct report *output = malloc(sizeof(struct report));

    struct indist **distanceList = malloc(points * sizeof(struct indist));

    double begin_dist = omp_get_wtime();

    if (par == 0)
    {
        if (distanceFunc == 0)
        {
            euclidianDistance_Serial(input, dataSet, distanceList, points, dim);
        }
        else if (distanceFunc == 1)
        {
            manhattanDistance_Serial(input, dataSet, distanceList, points, dim);
        }
    }
    else if (par == 1)
    {
        if (distanceFunc == 0)
        {
            euclidianDistance_Parallel(input, dataSet, distanceList, points, dim);
        }
        else if (distanceFunc == 1)
        {
            manhattanDistance_Parallel(input, dataSet, distanceList, points, dim);
        }
    }

    double end_dist = omp_get_wtime();
    //printf("Distance time: %f\n", end_dist - begin_dist);

    /*
    for (int j = 0; j < k; j++)
    {
        printf("%d: %f\n", distanceList[j]->index, distanceList[j]->dist);
    }

    printf("\n");

    */

    double begin_sort = omp_get_wtime();

    if (par == 1)
    {

        if (TASKS == 1)
        {

            {

                if (sortingFunc == 0)
                {
#pragma omp parallel shared(distanceList)
                    {
#pragma omp single
                        {
                            quickSort_Parallel_Tasks(distanceList, 0, points - 1, points, points);
                        }
                    }
                }
                else if (sortingFunc == 1)
                {
#pragma omp parallel shared(distanceList)
                    {
#pragma omp single
                        {
                            mergeSort_Parallel_Tasks(distanceList, 0, points - 1, points, points);
                        }
                    }
                }
                else if (sortingFunc == 2)
                {
#pragma omp parallel shared(distanceList)
                    {
#pragma omp single
                        {
                            bubbleSort_Parallel_Tasks(distanceList, 0, points - 1, points, points, omp_get_num_threads());
                        }
                    }
                }
                else
                {
                    printf("\nPlease select a number: 0, 1, or 2\n");
                    //return 0;
                }
            }
        }
        else
        {

            if (sortingFunc == 0)
            {
                quickSort_Parallel_Sections(distanceList, 0, points - 1, points, points);
            }
            else if (sortingFunc == 1)
            {
                mergeSort_Parallel_Sections(distanceList, 0, points - 1, points, points);
            }
            else if (sortingFunc == 2)
            {
                omp_set_num_threads(8);
                bubbleSort_Parallel_Sections(distanceList, 0, points - 1, points, points, 8);
            }
            else
            {
                printf("\nPlease select a number: 0, 1, or 2\n");
                //return 0;
            }
        }
    }
    else //Serial
    {
        //printf("PAR: %d\n", par);
        if (sortingFunc == 0)
        {
            quickSort_Serial(distanceList, 0, points - 1, points);
        }
        else if (sortingFunc == 1)
        {
            mergeSort_Serial(distanceList, 0, points - 1, points);
        }
        else if (sortingFunc == 2)
        {
            bubbleSort_Serial(distanceList, points);
        }
        else
        {
            printf("\nPlease select a number: 0, 1, or 2\n");
            return 0;
        }
    }

    double end_sort = omp_get_wtime();

    output->sorting = (double)(end_sort - begin_sort);
    output->distance = (double)(end_dist - begin_dist);

    /*
    for (int j = 0; j < k; j++)
    {
        printf("%d: %f\n", distanceList[j]->index, distanceList[j]->dist);
    }

    printf("\n");
    */
    for (int i = 0; i < points; i++)
    {
        free(distanceList[i]);
    }

    free(distanceList);

    return output;
}

//Compute the Manhattan distance between two points, requires dimension of points
double manhattanDistance(double *point1, double *point2, int dim)
{
    double sum = 0;
    for (int i = 0; i < dim; i++)
    {
        sum += abs(point1[i] - point2[i]);
    }

    return sum;
}

//Compute the Euclidean distance between two points, requires dimension of points
double euclideanDistance(double *point1, double *point2, int dim)
{
    double sum = 0;
    for (int i = 0; i < dim; i++)
    {
        sum += pow(point1[i] - point2[i], 2);
    }

    return sqrt(sum);
}

void manhattanDistance_Serial(double *input, double **dataSet, struct indist **distanceList, int points, int dim)
{
    for (int i = 0; i < points; i++)
    {
        struct indist *pair = malloc(sizeof(struct indist *));
        pair->index = i;
        pair->dist = manhattanDistance(input, dataSet[i], dim);
        distanceList[i] = pair;
    }
}

void manhattanDistance_Parallel(double *input, double **dataSet, struct indist **distanceList, int points, int dim)
{
#pragma omp parallel for
    for (int i = 0; i < points; i++)
    {
        struct indist *pair = malloc(sizeof(struct indist *));
        pair->index = i;
        pair->dist = manhattanDistance(input, dataSet[i], dim);
        distanceList[i] = pair;
    }
}

void euclidianDistance_Serial(double *input, double **dataSet, struct indist **distanceList, int points, int dim)
{
    for (int i = 0; i < points; i++)
    {
        struct indist *pair = malloc(sizeof(struct indist *));
        pair->index = i;
        pair->dist = euclideanDistance(input, dataSet[i], dim);
        distanceList[i] = pair;
    }
}

void euclidianDistance_Parallel(double *input, double **dataSet, struct indist **distanceList, int points, int dim)
{
#pragma omp parallel for
    for (int i = 0; i < points; i++)
    {
        struct indist *pair = malloc(sizeof(struct indist *));
        pair->index = i;
        pair->dist = euclideanDistance(input, dataSet[i], dim);
        distanceList[i] = pair;
    }
}