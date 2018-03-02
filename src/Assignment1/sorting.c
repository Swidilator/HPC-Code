#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void quickSort_Serial(struct indist *importList, struct indist *left, struct indist *right)
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


        quickSort_Serial(importList, left, i - 1);
        quickSort_Serial(importList, i + 1, right);

        
    }
}
