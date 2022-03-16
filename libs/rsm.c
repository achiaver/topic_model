#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rsm.h"

//random_seed(0);

double sigmoid (const double x) 
{
    return 1 / (1 + exp(-x));
}

double softmax (double *z, int nv, int k)
{
    double m = -INFINITY;
    double sum_exp = 0.0;
   
    // Find maximum value of weighted sum above
    for (int i = 0; i < nv; i++)
    {
        if (m < z[i])
        {
            m = z[i];
        }
    }

    // Computation of normalization factor
    // denominator of softmax
    for (int i = 0; i < nv; i++)
    {
        sum_exp += exp(z[i] - m);
    }
    
    return exp(z[k] - m - log(sum_exp));
}

double * sample_hidden_from_visible (const RSM_t *rsm_nn)
{
    double *h = calloc(rsm_nn->nh, sizeof(double*));
    for (int j = 0; j < rsm_nn->nh; j++)
    {
        double sum = 0.0;
        for (int i = 0; i < rsm_nn->nv; i++)
        {
            sum += rsm_nn->v[i] * rsm_nn->w[(i * rsm_nn->nh) + j];
        }
        h[j] = sigmoid(sum + rsm_nn->d * rsm_nn->b[rsm_nn->nv + j]);         
        fprintf(stdout, "p_h%d = %lf\n", j, h[j]);

        if (h[j] >= random_1())
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

double * sample_visible_from_hidden (const RSM_t *rsm_nn)
{
    double *v = calloc(rsm_nn->nv, sizeof(double *)); 
    double *temp_v = calloc(rsm_nn->nv, sizeof(double *));
    double *z = calloc(rsm_nn->nv, sizeof(double *));
    // Computation of weighted sum of inputs to visible units
    for (int k = 0; k < rsm_nn->nv; k++)
    {
        double sum = 0.0;
        for (int j = 0; j < rsm_nn->nh; j++)
        {
            sum += rsm_nn->h[j] * rsm_nn->w[(k * rsm_nn->nh) + j];
        }
        z[k] = sum + rsm_nn->b[k]; 
    }
    
    // Compute softmax for each visible and 
    // sample d (doc_size) each visible unit
    for (int k = 0; k < rsm_nn->nv; k++)
    {
        temp_v[k] = softmax(z, rsm_nn->nv, k);
        fprintf(stdout, "p_v%d = %lf\n", k, temp_v[k]);
        for (int i = 0; i < rsm_nn->d; i++)
        {
            if (temp_v[k] >= random_1())
            {
                v[k] += 1.0;
            }
        }
    }
    free(temp_v);
    free(z);
    return v;
}

void cdk (RSM_t *rsm_nn, double *input, double learning_rate, int ksteps)
{

}


void rsm_train (RSM_t *rsm_nn, const DATA_t *dataset, const PARAM_t *parameters)
{

}



RSM_t *rsm_build (const int nv, const int nh)
{
    RSM_t *rsm_nn = malloc(sizeof(*rsm_nn));
    rsm_nn->nb = nv + nh;
    rsm_nn->nw = nv * nh;
    rsm_nn->nv = nv;
    rsm_nn->nh = nh;
    rsm_nn->d = 0;
    rsm_nn->w = (double *) calloc(rsm_nn->nw, sizeof(*rsm_nn->w));
    rsm_nn->b = (double *) calloc(rsm_nn->nb, sizeof(*rsm_nn->b));
    rsm_nn->v = (double *) calloc(rsm_nn->nv, sizeof(*rsm_nn->v));
    rsm_nn->h = (double *) calloc(rsm_nn->nh, sizeof(rsm_nn->h));
    
    for (int l = 0; l < rsm_nn->nw; l++)
    {
        rsm_nn->w[l] = random_1();
    }
    
    for (int m = 0; m < rsm_nn->nb; m++)
    {
        rsm_nn->b[m] = random_1();
    }

    return rsm_nn;
}

void rsm_save (const RSM_t *rsm_nn, const char * path)
{
    fprintf(stdout, "*===== Saving RSM =====*\n"); 
    FILE * const file = fopen(path, "w");
    fprintf(file, "%d %d\n", rsm_nn->nv, rsm_nn->nh);
    fprintf(stdout, "Saving weights to file: %s\n", path); 
    for(int i = 0; i < rsm_nn->nw; i++)
    {
        fprintf(file, "%lf\n", rsm_nn->w[i]);
    }

    fprintf(stdout, "Saving biases to file: %s\n", path);  
    for(int i = 0; i < rsm_nn->nb; i++)
    {
        fprintf(file, "%lf\n", rsm_nn->b[i]);
    }
    
    fprintf(stdout, "*===== Saving complete =====*\n\n");
    fclose(file);
}

RSM_t *rsm_load (const char * path)
{
    fprintf(stdout, "*===== Loading RSM =====*\n"); 
    FILE * const file = fopen(path, "r");
    int nv = 0;
    int nh = 0;

    fscanf(file, "%d %d\n", &nv, &nh);

    RSM_t *rsm_nn = rsm_build(nv, nh);
    
    fprintf(stdout, "Reading in weights from file: %s\n", path);
    for(int i = 0; i < rsm_nn->nw; i++)
    {
        fscanf(file, "%lf\n", &rsm_nn->w[i]);
    }
    
    fprintf(stdout, "Reading in biases from file: %s\n", path);
    for(int i = 0; i < rsm_nn->nb; i++)
    {
        fscanf(file, "%lf\n", &rsm_nn->b[i]);
    }

    fclose(file);
    fprintf(stdout, "*===== Loading complete =====*\n\n");
    return rsm_nn;
}

void rsm_print (const RSM_t *rsm_nn)
{
    fprintf(stdout, "\n");
    fprintf(stdout, "*===== Replicated Softmax Setup =====*\n");
    fprintf(stdout, "Number of visible units: %d\n", rsm_nn->nv);
    fprintf(stdout, "Number of hidden units: %d\n", rsm_nn->nh);
    fprintf(stdout, "Number of weights: %d\n", rsm_nn->nw);
    fprintf(stdout, "Number of biases: %d\n\n", rsm_nn->nb);
    fprintf(stdout, "Weights - \n");
    for (int k = 0; k < rsm_nn->nv; k++)
    {
        for (int j = 0; j < rsm_nn->nh; j++)
        {
            fprintf(stdout, "%4.6lf\t", rsm_nn->w[(k * rsm_nn->nh) + j]);
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");

    fprintf(stdout, "Biases - \n");
    for (int k = 0; k < rsm_nn->nv; k++)
    {
        fprintf(stdout, "%4.6lf\n", rsm_nn->b[k]);
    }
    for (int j = 0; j < rsm_nn->nh; j++)
    {
        fprintf(stdout, "%4.6lf\n", rsm_nn->b[rsm_nn->nv + j]);
    }
    fprintf(stdout, "\n\n");
}

void rsm_free (RSM_t *rsm_nn)
{
    free(rsm_nn->w);
    free(rsm_nn->b);
    free(rsm_nn->v);
    free(rsm_nn);
}
 
