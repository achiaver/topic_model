#include <stdio.h>
#include <stdlib.h>
#include "parameters.h"


PARAM_t *parameters_create(void)
{
    PARAM_t *parameters = calloc(1, sizeof(parameters));
    if (!parameters)
    {
        fprintf(stdout, "parameters_create: calloc: \n");
        exit(2);
    }
    return parameters;
}

PARAM_t *parameters_readin(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stdout, "parameters_readin: fopen: \n");
        exit(2);
    }

    PARAM_t *parameters = parameters_create();
    fscanf(file, 
        "%*s%s%*s \
         %*s%s%*s \
         %*s%s%*s \
         %*s%d%*s \
         %*s%d%*s \
         %*s%d%*s \
         %*s%d%*s \
         %*s%d%*s \
         %*s%d%*s",
        parameters->dataset_filename,
        parameters->weights_filename,
        parameters->biases_filename,
        &parameters->dataset_rows,
        &parameters->dataset_cols,
        &parameters->num_weights,
        &parameters->num_biases,
        &parameters->num_vis,
        &parameters->num_hid);
    fclose(file);
    if (parameters->num_vis != parameters->dataset_cols)
    {
        fprintf(stdout, "parameters_readin: number of visible units and dataset columns should match\n");
        exit(2);    
    }

    if (parameters->num_vis * parameters->num_hid != parameters->num_weights)
    {
        fprintf(stdout, "parameters_readin: number of weights should match number of visible units * number of hidden units\n");
        exit(2);
    }

    if (parameters->num_vis + parameters->num_hid != parameters->num_biases)
    {
        fprintf(stdout, "parameters_readint: number of biases should match number of visible units + number of hidden units\n");
        exit(2);
    }

    return parameters;
}

void parameters_delete(PARAM_t *parameters)
{
    if (!parameters)
    {
        free(parameters->dataset_filename);
        free(parameters->weights_filename);
        free(parameters->biases_filename);
        free(parameters);
    }
}

void parameters_print(const PARAM_t *parameters)
{
    fprintf(stdout, "Dataset filename: %s\n", parameters->dataset_filename);
    fprintf(stdout, "Weights filename: %s\n", parameters->weights_filename);
    fprintf(stdout, "Biases filename: %s\n", parameters->biases_filename);
    fprintf(stdout, "Number of Rows in Dataset: %d\n", parameters->dataset_rows);      
    fprintf(stdout, "Number of Cols in Dataset: %d\n", parameters->dataset_cols);
    fprintf(stdout, "Number of Weights: %d\n", parameters->num_weights);
    fprintf(stdout, "Number of Biases: %d\n", parameters->num_biases);
    fprintf(stdout, "Number of Visible units: %d\n", parameters->num_vis); 
    fprintf(stdout, "Number of Hidden units: %d\n", parameters->num_hid); 
}
