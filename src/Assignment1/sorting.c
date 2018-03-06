#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include <omp.h>

typedef enum { false,
               true } bool;

void quickSort_Serial(struct indist **importList, int left, int right, int points)
{
    if (right > left)
    {
        double v = importList[right]->dist;
        int i = left;
        int j = right;
        while (i < j)
        {
            while (importList[i]->dist < v)
            {
                i = i + 1;
            }
            while (j > i && importList[j]->dist >= v)
            {
                j = j - 1;
            }

            if (j > i)
            {
                double t = importList[i]->dist;
                int tInd = importList[i]->index;
                importList[i]->dist = importList[j]->dist;
                importList[i]->index = importList[j]->index;
                importList[j]->dist = t;
                importList[j]->index = tInd;
            }
            else
            {
                double t = importList[i]->dist;
                int tInd = importList[i]->index;
                importList[i]->dist = importList[right]->dist;
                importList[i]->index = importList[right]->index;
                importList[right]->dist = t;
                importList[right]->index = tInd;
            }
        }

        quickSort_Serial(importList, left, (i - 1), (i - 1) - left + 1);
        quickSort_Serial(importList, i + 1, right, right - (i + 1) + 1);
    }
}

void mergeSort_Serial(struct indist **importList, int left, int right, int points)
{

    if (right - left > 0)
    {
        //struct indist *mid = importList[(int)floor((right + left)/2)];
        int mid = (right + left) / 2;
        mergeSort_Serial(importList, left, mid, mid - left + 1);
        mergeSort_Serial(importList, mid + 1, right, right - (mid));

        struct indist **temp = malloc((points) * sizeof(struct indist *));

        for (int i = mid; i >= left; i--)
        {
            struct indist *pair = malloc(sizeof(struct indist));
            pair->dist = importList[i]->dist;
            pair->index = importList[i]->index;
            temp[i - left] = pair;
        }

        for (int j = mid + 1; j <= right; j++)
        {
            struct indist *pair = malloc(sizeof(struct indist *));

            pair->dist = importList[j]->dist;
            pair->index = importList[j]->index;
            temp[right + mid + 1 - j - left] = pair;
        }

        int i = left;
        int j = right;

        for (int k = left; k <= right; k++)
        {
            if (temp[i - left]->dist < temp[j - left]->dist)
            {
                importList[k]->dist = temp[i - left]->dist;
                importList[k]->index = temp[i - left]->index;
                free(temp[i - left]);
                i = i + 1;
            }
            else
            {
                importList[k]->dist = temp[j - left]->dist;
                importList[k]->index = temp[j - left]->index;
                free(temp[j - left]);
                j = j - 1;
            }
        }
        free(temp);
    }
}

void bubbleSort_Serial(struct indist **importList, int points)
{
    int i = points - 1;
    bool sorting = true;
    while (i >= 1 && sorting == true)
    {
        bool swopped = false;
        for (int j = 0; j < i - 1; j++)
        {
            if (importList[j]->dist > importList[j + 1]->dist)
            {
                //swop
                double t = importList[j]->dist;
                int tInd = importList[j]->index;

                importList[j]->dist = importList[j + 1]->dist;
                importList[j]->index = importList[j + 1]->index;

                importList[j + 1]->dist = t;
                importList[j + 1]->index = tInd;

                swopped = true;
            }
        }
        if (swopped == false)
        {
            sorting = false;
        }
        else
        {
            i = i - 1;
        }
    }
}

void quickSort_Parallel_Sections(struct indist **importList, int left, int right, int points, int pointsTotal)
{
    //omp_set_num_threads(4);
    if (right > left)
    {
        double v = importList[right]->dist;
        int i = left;
        int j = right;
        while (i < j)
        {
            while (importList[i]->dist < v)
            {
                i = i + 1;
            }
            while (j > i && importList[j]->dist >= v)
            {
                j = j - 1;
            }

            if (j > i)
            {
                double t = importList[i]->dist;
                int tInd = importList[i]->index;
                importList[i]->dist = importList[j]->dist;
                importList[i]->index = importList[j]->index;
                importList[j]->dist = t;
                importList[j]->index = tInd;
            }
            else
            {
                double t = importList[i]->dist;
                int tInd = importList[i]->index;
                importList[i]->dist = importList[right]->dist;
                importList[i]->index = importList[right]->index;
                importList[right]->dist = t;
                importList[right]->index = tInd;
            }
        }

        if (right - left < pointsTotal / 8)
        {
            quickSort_Serial(importList, left, (i - 1), (i - 1) - left + 1);
            quickSort_Serial(importList, i + 1, right, right - (i + 1) + 1);
        }
        else
        {
            omp_set_nested(1);
#pragma omp parallel shared(importList)
            {
#pragma omp sections
                {
#pragma omp section
                    {
                        quickSort_Parallel_Sections(importList, left, (i - 1), (i - 1) - left + 1, pointsTotal);
                    }
#pragma omp section
                    {
                        quickSort_Parallel_Sections(importList, i + 1, right, right - (i + 1) + 1, pointsTotal);
                    }
                }
            }
        }
    }
}

void quickSort_Parallel_Tasks(struct indist **importList, int left, int right, int points, int pointsTotal)
{
    omp_set_num_threads(8);
    if (right > left)
    {
        double v = importList[right]->dist;
        int i = left;
        int j = right;
        while (i < j)
        {
            while (importList[i]->dist < v)
            {
                i = i + 1;
            }
            while (j > i && importList[j]->dist >= v)
            {
                j = j - 1;
            }

            if (j > i)
            {
                double t = importList[i]->dist;
                int tInd = importList[i]->index;
                importList[i]->dist = importList[j]->dist;
                importList[i]->index = importList[j]->index;
                importList[j]->dist = t;
                importList[j]->index = tInd;
            }
            else
            {
                double t = importList[i]->dist;
                int tInd = importList[i]->index;
                importList[i]->dist = importList[right]->dist;
                importList[i]->index = importList[right]->index;
                importList[right]->dist = t;
                importList[right]->index = tInd;
            }
        }

        if (right - left < pointsTotal / 1024)
        {
            quickSort_Serial(importList, left, (i - 1), (i - 1) - left + 1);
            quickSort_Serial(importList, i + 1, right, right - (i + 1) + 1);
        }
        else
        {
#pragma omp task
            {
                quickSort_Parallel_Sections(importList, left, (i - 1), (i - 1) - left + 1, pointsTotal);
            }
#pragma omp task
            {
                quickSort_Parallel_Sections(importList, i + 1, right, right - (i + 1) + 1, pointsTotal);
            }
        }
    }
}

void mergeSort_Parallel_Sections(struct indist **importList, int left, int right, int points, int pointsTotal)
{
    omp_set_num_threads(8);
    if (right - left > 0)
    {
        int mid = (right + left) / 2;

        if (right - left < pointsTotal / 8)
        {
            mergeSort_Serial(importList, left, mid, mid - left + 1);
            mergeSort_Serial(importList, mid + 1, right, right - (mid));
        }
        else
        {
            {
                omp_set_nested(1);
#pragma omp parallel shared(importList)
                {
#pragma omp sections
                    {
#pragma omp section
                        {
                            mergeSort_Parallel_Sections(importList, left, mid, mid - left + 1, pointsTotal);
                        }
#pragma omp section
                        {
                            mergeSort_Parallel_Sections(importList, mid + 1, right, right - (mid), pointsTotal);
                        }
                    }
                }
            }
        }

        struct indist **temp = malloc((points) * sizeof(struct indist *));
        for (int i = mid; i >= left; i--)
        {
            struct indist *pair = malloc(sizeof(struct indist));
            pair->dist = importList[i]->dist;
            pair->index = importList[i]->index;
            temp[i - left] = pair;
        }

        for (int j = mid + 1; j <= right; j++)
        {
            struct indist *pair = malloc(sizeof(struct indist *));

            pair->dist = importList[j]->dist;
            pair->index = importList[j]->index;
            temp[right + mid + 1 - j - left] = pair;
        }

        int i = left;
        int j = right;

        for (int k = left; k <= right; k++)
        {
            if (temp[i - left]->dist < temp[j - left]->dist)
            {
                importList[k]->dist = temp[i - left]->dist;
                importList[k]->index = temp[i - left]->index;
                free(temp[i - left]);
                i = i + 1;
            }
            else
            {
                importList[k]->dist = temp[j - left]->dist;
                importList[k]->index = temp[j - left]->index;
                free(temp[j - left]);
                j = j - 1;
            }
        }
        free(temp);
    }
}

void mergeSort_Parallel_Tasks(struct indist **importList, int left, int right, int points, int pointsTotal)
{
    omp_set_num_threads(8);
    if (right - left > 0)
    {
        int mid = (right + left) / 2;

        if (right - left < pointsTotal / 1024)
        {
            mergeSort_Serial(importList, left, mid, mid - left + 1);
            mergeSort_Serial(importList, mid + 1, right, right - (mid));
        }
        else
        {
            {
#pragma omp task
                {
                    mergeSort_Parallel_Tasks(importList, left, mid, mid - left + 1, pointsTotal);
                }
#pragma omp task
                {
                    mergeSort_Parallel_Tasks(importList, mid + 1, right, right - (mid), pointsTotal);
                }
            }
        }

        struct indist **temp = malloc((points) * sizeof(struct indist *));
        for (int i = mid; i >= left; i--)
        {
            struct indist *pair = malloc(sizeof(struct indist));
            pair->dist = importList[i]->dist;
            pair->index = importList[i]->index;
            temp[i - left] = pair;
        }

        for (int j = mid + 1; j <= right; j++)
        {
            struct indist *pair = malloc(sizeof(struct indist *));

            pair->dist = importList[j]->dist;
            pair->index = importList[j]->index;
            temp[right + mid + 1 - j - left] = pair;
        }

        int i = left;
        int j = right;

        for (int k = left; k <= right; k++)
        {
            if (temp[i - left]->dist < temp[j - left]->dist)
            {
                importList[k]->dist = temp[i - left]->dist;
                importList[k]->index = temp[i - left]->index;
                free(temp[i - left]);
                i = i + 1;
            }
            else
            {
                importList[k]->dist = temp[j - left]->dist;
                importList[k]->index = temp[j - left]->index;
                free(temp[j - left]);
                j = j - 1;
            }
        }
        free(temp);
    }
}