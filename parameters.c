#include "parameters.h"

PARAM_t *parameters_create(void)
{
    PARAM_t parameters = calloc(1, sizeof(PARAM_t));
    if (!parameters)
    {
        fprintf(stdout, "parameters_create: calloc: %s %d");
        exit(2);
    }
    return parameters;

PARAM_t *parameters_readin(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stdout, "parameters_readin: fopen: %s %d");
        exit(2);
    }

    PARAM_t parameters = parameters_create();
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
        parameters.dataset_filename,
        parameters.weights_filename,
        parameters.biases_filename,
        &parameters.dataset_rows,
        &parameters.dataset_cols,
        &parameters.num_weights,
        &parameters.num_biases,
        &parameters.num_vis,
        &parameters.num_hid)

    fclose(file);
    if (parameters.num_vis != parameters.dataset_cols)
    {
        fprintf(stdout, "parameters_readin: number of visible units and dataset columns should match");
        exit(2);    
    }

    if (parameters.num_vis * parameters.num_hid != parameters.num_weights)
    {
        fprintf(stdout, "parameters_readin: number of weights should match number of visible units * number of hidden units");
        exit(2);
    }

    if (parameters.num_vis + parameters.num_hid != parameters.num_biases)
    {
        fprintf(stdout, "parameters_readint: number of biases should match number of visible units + number of hidden units");
        exit(2);
    }

    return parameters;
}