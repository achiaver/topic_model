#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rsm.h"


int iseed = -42;

double sigmoid(const double x) 
{
    return 1 / (1 + exp(-x));
}

double * sample_hidden_from_visible(const RSM_t *rsm_nn)
{
    double *h = calloc(rsm_nn->nh, sizeof(double*));
    for (int j = 0; j < rsm_nn->nh; j++)
    {
        double sum = 0.0;
        for (int i = 0; i < rsm_nn->nv; i++)
        {
            sum += rsm_nn->v[i] * rsm_nn->w[(i * rsm_nn->nh) + j];
        }
        h[j] = sigmoid(sum + rsm_nn->b[rsm_nn->nv + j]);
        
        if (h[j] >= rand_1(&iseed))
        {
            h[j] = 1.0;
        }
        else
        {
            h[j] = 0.0;
        }
    }
    return h;
}

double * sample_visible_from_hidden(const RSM_t *rsm_nn)
{
    double *v = calloc(rsm_nn->nv, sizeof(double*));
    for (int i = 0; i < rsm_nn->nv; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < rsm_nn->nh; j++)
        {
            sum += rsm_nn->h[j] * rsm_nn->w[(i * rsm_nn->nh) + j];
        }
        v[i] = sigmoid(sum + rsm_nn->b[i]);

        if (v[i] >= rand_1(&iseed))
        {}
        else
        {}
    }
}


RSM_t *rsm_build(const int nv, const int nh)
{
    RSM_t *rsm_nn;
    rsm_nn->nb = nv + nh;
    rsm_nn->nw = nv * nh;
    rsm_nn->nv = nv;
    rsm_nn->nh = nh;
    rsm_nn->w = (double *) calloc(rsm_nn->nw, sizeof(*rsm_nn->w));
    rsm_nn->b = (double *) calloc(rsm_nn->nb, sizeof(*rsm_nn->b));
    rsm_nn->v = (int *) calloc(rsm_nn->nv, sizeof(*rsm_nn->v));
    rsm_nn->h = (int *) calloc(rsm_nn->nh, sizeof(rsm_nn->h));
    
    return rsm_nn;
}

void rsm_save(const RSM_t *rsm_nn, const char * path)
{
    FILE * const file = fopen(path, "w");
    fprintf(file, "%d %d\n", rsm_nn->nv, rsm_nn->nh);
    
    for(int i = 0; i <= rsm_nn->nb; i++)
    {
        fprintf(file, "%lf\n", rsm_nn->b[i]);
    }

    for(int i = 0; i <= rsm_nn->nw; i++)
    {
        fprintf(file, "%lf\n", rsm_nn->w[i]);
    }

    fclose(file);
}

RSM_t *rsm_load(const char * path)
{
    FILE * const file = fopen(path, "r");
    int nv = 0;
    int nh = 0;

    fscanf(file, "%d %d\n", &nv, &nh);

    const RSM_t *rsm_nn = rsm_build(nv, nh);

    for(int i = 0; i <= rsm_nn->nb; i++)
    {
        fscanf(file, "%lf\n", &rsm_nn->b[i]);
    }

    for(int i = 0; i <= rsm_nn->nw; i++)
    {
        fscanf(file, "%lf\n", &rsm_nn->w[i]);
    }
    fclose(file);
    return rsm_nn;
}

void rsm_print(const double * arr, const int size)
{

}

void rsm_free(RSM_t *rsm_nn)
{
    free(rsm_nn->w);
    free(rsm_nn->b);
    free(rsm_nn->v);
    free(rsm_nn);
}
 
