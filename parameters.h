#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

typedef struct parameters
{
    char dataset_filename[256];
    char weights_filename[256];
    char biases_filename[256];
    int dataset_rows;
    int dataset_cols;
    int num_weights;
    int num_biases;
    int num_vis;
    int num_hid;
} PARAM_t;

PARAM_t *parameters_create(void);
PARAM_t *parameters_readin(char *filename);
void     parameters_delete(const PARAM_t parameters);
void     parameters_print(const PARAM_t paraneters);

#endif