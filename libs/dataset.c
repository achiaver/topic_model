/* =============================================================================
 * =============================================================================
 * dataset.c - 
 * contains functions related to dataset management.
 * 
 * dataset is stored into matrix:
 *  -> rows = set of inputs, each row is an occurrence of the observed phenomenon
 *  -> cols = set of dimensions, each col is one input to a single 
 *            node (cols = number of visible nodes)
 *
 * DATA_t definitions can be found on matrix.h
 * 
 *
 * =============================================================================
 * =============================================================================
 */

#include "dataset.h"
#include <stdio.h>
#include <string.h>


// dataset_allocate read in the dataset from a txt (.csv) file and store the data
// on a matrix.

DATA_t *data_allocate (int rows, int cols)
{
    DATA_t *dataset = calloc(1, sizeof(*dataset));
    if (!dataset)
    {
        fprintf(stdout, "data_allocate: DATA_t: calloc: %s %d\n", __FILE__, __LINE__);
        exit(2);
    }
    dataset->rows = rows;
    dataset->cols = cols;
    dataset->inputs = calloc((dataset->rows * dataset->cols), sizeof(double));
    if (!dataset->inputs)
    {
        fprintf(stdout, "data_allocate: DATA_t->inputs: calloc: %s %d\n", __FILE__, __LINE__);
        exit(2);
    }

    return dataset;
}

DATA_t *data_readin (char *filename)
{
    int rows = 0;
    int cols = 0;
    char buffer[2048];
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        fprintf(stdout, "data_readin: fopen: %s %d\n", __FILE__, __LINE__);
        exit(2);
    }
    fscanf(fp, "%d,%d\n", &rows, &cols);

    DATA_t *dataset = data_allocate(rows, cols);
    int count_rows = 0;
    int count_cols = 0;
    while(fgets(buffer, sizeof(buffer), fp) && (count_rows < dataset->rows))
    {
        char *value;
        for (value = strtok(buffer, ","), count_cols = 0; count_cols < dataset->cols; count_cols++, value = strtok(NULL, ",\n"))
        {
            dataset->inputs[(count_rows * dataset->cols) + count_cols] = atof(value); 
        }
        count_rows += 1;
    }
    fclose(fp);
    return dataset;
} /* end dataset_allocate */


void data_free (DATA_t *dataset)
{
    if (dataset)
    {
        free(dataset->inputs);
        free(dataset);
    }
} /* end dataset_destroy */


// dataset_dump display the whole dataset DATA_t in the prompt.

void data_dump(DATA_t *dataset)
{
    fprintf(stdout, "*===== Dataset Dump =====*\n\n");
    for (int row = 0; row < dataset->rows; row++)
    {
        fprintf(stdout, "[%6d] -\t", row);
        for (int col = 0; col < dataset->cols; col++)
        {
            fprintf(stdout, "%6.1f\t", dataset->inputs[(row * dataset->cols) + col]);
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
} /* end dataset_print */
