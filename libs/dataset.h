#ifndef __DATASET_H__
#define __DATASET_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data
{
    int rows;
    int cols;
    double *inputs;
} DATA_t;

DATA_t *data_readin (char *filename);
void data_free (DATA_t *dataset);
void data_dump (DATA_t *dataset);

#endif /* __DATASET_H__ */
