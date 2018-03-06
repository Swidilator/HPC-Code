#include "dataGen.h"
#include <stdlib.h>
#include <omp.h>

double **makeDataset(int dim, int points, int min, int max)
{

    //2D array for points
    double **rows = malloc(points * sizeof(double *));

    
    for (int i = 0; i < points; i++)
    {
        double *dataPoint = malloc(dim * sizeof(double));
        //#pragma omp parallel for
        for (int j = 0; j < dim; j++)
        {
            //Make number in the range of what is passed in
            dataPoint[j] = ((max - min) * (double)rand() / (double)RAND_MAX + min);
        }
        rows[i] = dataPoint;
    }
    return rows;
}