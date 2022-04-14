#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "random_lib.h"
#include "parameters.h"
#include "dataset.h"

typedef struct rsm_nn
{
    double *w;  // weights array
    double *b;  // biases array
    int nw;     // number of weights 
    int nb;     // number of biases
    int nv;     // number of visible units
    int nh;     // number of hidden units
    int d;
} RSM_t;

RSM_t *rsm_build (const int nv, const int nh);
void rsm_save (const RSM_t *rsm, const char * path);
RSM_t *rsm_load (const char * path);
void rsm_print (const RSM_t *rsm);
void rsm_free (RSM_t *rsm);

void rsm_train (RSM_t *rsm, const DATA_t *dataset, const PARAM_t *parameters);
void rsm_predict (RSM_t *rsm, const DATA_t *dataset, double *visible);
double *sample_hidden_from_visible (const RSM_t *rsm, double *v);
double *sample_visible_from_hidden (const RSM_t *rsm, double *h);

