#include "rsm.h"

//random_seed(0);

double sigmoid (const double x) 
{
    return 1 / (1 + exp(-x));
} /* end sigmoid */

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
} /* end softmax*/

void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
} /* end swap */


void shuffle (int arr[], int n)
{
    for (int i = n-1; i > 0; i--)
    {
        int j = random_bound(i+1); // Pick a random index from 0 to i
//        printf("j - %d\n", j);
        swap(&arr[i], &arr[j]);
    }
} /* end shuffle */

double * sample_hidden_from_visible (const RSM_t *rsm, double *v)
{
    double *h = calloc(rsm->nh, sizeof(*h));
    for (int j = 0; j < rsm->nh; j++)
    {
        double sum = 0.0;
        for (int i = 0; i < rsm->nv; i++)
        {
            sum += v[i] * rsm->w[(i * rsm->nh) + j];
        }
        h[j] = sigmoid(sum + rsm->d * rsm->b[rsm->nv + j]);         
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
} /* end sample_hidden_from_visible */

double * sample_visible_from_hidden (const RSM_t *rsm, double *h)
{
    double *v = calloc(rsm->nv, sizeof(*v)); 
    double *temp_v = calloc(rsm->nv, sizeof(*temp_v));
    double *z = calloc(rsm->nv, sizeof(*z));
    // Computation of weighted sum of inputs to visible units
    for (int k = 0; k < rsm->nv; k++)
    {
        double sum = 0.0;
        for (int j = 0; j < rsm->nh; j++)
        {
            sum += h[j] * rsm->w[(k * rsm->nh) + j];
        }
        z[k] = sum + rsm->b[k]; 
    }
    
    // Compute softmax for each visible and 
    // sample d (doc_size) each visible unit
    for (int k = 0; k < rsm->nv; k++)
    {
        temp_v[k] = softmax(z, rsm->nv, k);
        fprintf(stdout, "p_v%d = %lf\n", k, temp_v[k]);
        for (int i = 0; i < rsm->d; i++)
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
} /* end sample_visible_from_hidden */

void update_weights (RSM_t *rsm, double *v0, double *h0, double *vt, double *ht, double learning_rate)
{
    for (int j = 0; j < rsm->nh; j++)
    {
        for (int k = 0; k < rsm->nv; k++)
        {
            rsm->w[(k * rsm->nh) + j] += learning_rate * ((v0[k] * h0[j]) - (vt[k] * ht[j]));
        }
        rsm->b[rsm->nv + j] += learning_rate * (h0[j] - ht[j]);
    }
    for (int k = 0; k < rsm->nv; k++)
    {
        rsm->b[k] += learning_rate * (v0[k] - vt[k]);
    }
} /* end update_weights */


void cdt (RSM_t *rsm, double *input, double learning_rate, int tsteps)
{
    double *h0 = calloc(rsm->nh, sizeof(*h0));
    double *vt = calloc(rsm->nv, sizeof(*vt));
    double *ht = calloc(rsm->nh, sizeof(*ht));

    h0 = sample_hidden_from_visible(rsm, input);
    vt = sample_visible_from_hidden(rsm, h0);
    ht = sample_hidden_from_visible(rsm, vt); 

    if (tsteps == 1)
    {
        update_weights(rsm, input, h0, vt, ht, learning_rate);
    }
    else
    {
        for (int t = 0; t < tsteps; t++)
        {
            vt = sample_visible_from_hidden(rsm, ht);
            ht = sample_hidden_from_visible(rsm, vt); 
        }
        update_weights(rsm, input, h0, vt, ht, learning_rate);
    }
    free(h0);
    free(vt);
    free(ht);
} /* end cdt*/


void rsm_train (RSM_t *rsm, const DATA_t *dataset, const PARAM_t *parameters)
{
    // FAZER shuffle no dataset
    // Para cada dado calcular D, somando os valores as entradas no input
    // salvar D na rede
    // definir as epochs
    // definir condicao de parada 
    int *indexes = calloc(dataset->rows, sizeof(*indexes));
    if (!indexes)
    {
        fprintf(stdout, "rsm_train: calloc: indexes: %s %d\n", __FILE__, __LINE__);
        exit(2);
    }
    for (int idx = 0; idx < dataset->rows; idx++)
    {
        indexes[idx] = idx;
    }
    
    int epoch = 0;
    // ADICIONAR EPOCHS em PARAM_t
    while (epoch < parameters->epochs)
    {
        shuffle(indexes, dataset->rows);
        
        for (int idx = 0; idx < dataset->rows; idx++)
        {
            int row = indexes[idx];
            int D = 0;
            double *input = calloc(dataset->cols, sizeof(*input));
            for (int in = 0; in < dataset->cols; in++)
            {
                input[in] = dataset->inputs[(row * dataset->cols) + in];
                D += input[in];
            }
            rsm->d = D; 
            cdt(rsm, input, parameters->learning_rate, parameters->tsteps);
        }
        epoch++;
    }

    free(indexes);
} /* end rsm_train*/ 



RSM_t *rsm_build (const int nv, const int nh)
{
    RSM_t *rsm = malloc(sizeof(*rsm));
    rsm->nb = nv + nh;
    rsm->nw = nv * nh;
    rsm->nv = nv;
    rsm->nh = nh;
    rsm->d = 0;
    rsm->w = (double *) calloc(rsm->nw, sizeof(*rsm->w));
    rsm->b = (double *) calloc(rsm->nb, sizeof(*rsm->b));
//    rsm->v = (double *) calloc(rsm->nv, sizeof(*rsm->v));
//    rsm->h = (double *) calloc(rsm->nh, sizeof(rsm->h));
    
    for (int l = 0; l < rsm->nw; l++)
    {
        rsm->w[l] = random_1();
    }
    
    for (int m = 0; m < rsm->nb; m++)
    {
        rsm->b[m] = random_1();
    }

    return rsm;
} /* end rsm_build */

void rsm_save (const RSM_t *rsm, const char * path)
{
    fprintf(stdout, "*===== Saving RSM =====*\n"); 
    FILE * const file = fopen(path, "w");
    fprintf(file, "%d %d\n", rsm->nv, rsm->nh);
    fprintf(stdout, "Saving weights to file: %s\n", path); 
    for(int i = 0; i < rsm->nw; i++)
    {
        fprintf(file, "%lf\n", rsm->w[i]);
    }

    fprintf(stdout, "Saving biases to file: %s\n", path);  
    for(int i = 0; i < rsm->nb; i++)
    {
        fprintf(file, "%lf\n", rsm->b[i]);
    }
    
    fprintf(stdout, "*===== Saving complete =====*\n\n");
    fclose(file);
} /* end rsm_save */

RSM_t *rsm_load (const char * path)
{
    fprintf(stdout, "*===== Loading RSM =====*\n"); 
    FILE * const file = fopen(path, "r");
    int nv = 0;
    int nh = 0;

    fscanf(file, "%d %d\n", &nv, &nh);

    RSM_t *rsm = rsm_build(nv, nh);
    
    fprintf(stdout, "Reading in weights from file: %s\n", path);
    for(int i = 0; i < rsm->nw; i++)
    {
        fscanf(file, "%lf\n", &rsm->w[i]);
    }
    
    fprintf(stdout, "Reading in biases from file: %s\n", path);
    for(int i = 0; i < rsm->nb; i++)
    {
        fscanf(file, "%lf\n", &rsm->b[i]);
    }

    fclose(file);
    fprintf(stdout, "*===== Loading complete =====*\n\n");
    return rsm;
} /* end rsm_load */

void rsm_print (const RSM_t *rsm)
{
    fprintf(stdout, "\n");
    fprintf(stdout, "*===== Replicated Softmax Setup =====*\n");
    fprintf(stdout, "Number of visible units: %d\n", rsm->nv);
    fprintf(stdout, "Number of hidden units: %d\n", rsm->nh);
    fprintf(stdout, "Number of weights: %d\n", rsm->nw);
    fprintf(stdout, "Number of biases: %d\n\n", rsm->nb);
    fprintf(stdout, "Weights - \n");
    for (int k = 0; k < rsm->nv; k++)
    {
        for (int j = 0; j < rsm->nh; j++)
        {
            fprintf(stdout, "%4.6lf\t", rsm->w[(k * rsm->nh) + j]);
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");

    fprintf(stdout, "Biases - \n");
    for (int k = 0; k < rsm->nv; k++)
    {
        fprintf(stdout, "%4.6lf\n", rsm->b[k]);
    }
    for (int j = 0; j < rsm->nh; j++)
    {
        fprintf(stdout, "%4.6lf\n", rsm->b[rsm->nv + j]);
    }
    fprintf(stdout, "\n\n");
} /* end rsm_print */

void rsm_free (RSM_t *rsm)
{
    free(rsm->w);
    free(rsm->b);
//    free(rsm->v);
    free(rsm);
} /* end rsm_free */
 
