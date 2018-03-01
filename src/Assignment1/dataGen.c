#include "dataGen.h"
#include <time.h>
#include <stdlib.h>



double** makeDataset(int dim, int points, int min, int max){

    srand(time(NULL));
    
    double** rows = malloc(points * sizeof(double*));

    for(int i = 0; i < points; i++){
        double* dataPoint = malloc(dim * sizeof(double));
        for(int j = 0; j < dim; j++){
            dataPoint[j] = ((max - min) * (double)rand()/(double)RAND_MAX + min);
        }
        rows[i] = dataPoint;
    }

    return rows;
}