#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"

void quickSort_Serial( struct indist *left, struct indist *right)
{
    if (right > left)
    {
        double v = right->dist;
        struct indist *i = left;
        struct indist *j = right;
        while (i < j)
        {
            while (i->dist < v)
            {
                i = i + 1;
            }
            while (j > i && j->dist >= v)
            {
                j = j - 1;
            }

            if (j > i)
            {
                double t = i->dist;
                int tInd = i->index;
                i->dist = j->dist;
                i->index = j->index;
                j->dist = t;
                j->index = tInd;
            }
            else
            {
                double t = i->dist;
                int tInd = i->index;
                i->dist = right->dist;
                i->index = right->index;
                right->dist = t;
                right->index = tInd;
            }
        }

        quickSort_Serial(left, i - 1);
        quickSort_Serial(i + 1, right);
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
                i = i + 1;
            }
            else
            {
                importList[k]->dist = temp[j - left]->dist;
                importList[k]->index = temp[j - left]->index;
                j = j - 1;
            }
        }
    }
}
