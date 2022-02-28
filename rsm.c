#include "rsm.h"

double sigmoid(const double x) 
{
    sig = 1 / (1 + exp(-x));
    return sig;
}

double * sample_hidden_from_visible(const RMS_t rsm_nn, )
{
    double h[rsm_nn.nh] = {0.0};
    for (int i = 0; i < rsm_nn.nh; i++)
    {
        double sum = 0;
        for (int j = 0; j < rsm_nn.nv; j++)
        {
            sum += 
        }
    }
}


RSM_t rsm_build(const int nv, const int nh)
{
    RSM_t rsm_nn;
    rsm_nn.nb = nv + nh;
    rsm_nn.nw = nv * nh;
    rsm_nn.nv = nv;
    rsm_nn.nh = nh;
    rsm_nn.w = (double *) calloc(rsm_nn.nw, sizeof(*rsm_nn.w));
    rsm_nn.b = (double *) calloc(rsm_nn.nb, sizeof(*rsm_nn.b));
    rsm_nn.v = (int *) calloc(rsm_nn.nv, sizeof(*rsm_nn.v));
    rsm_nn.h = (int *) calloc(rsm_nn.nh, sizeof(rsm_nn.h));
    
    return rsm_nn;
}

void rsm_save(const RSM_t rsm_nn, const char * path)
{
    FILE * const file = fopen(path, "w");
    fprintf(file, "%d %d\n", rsm_nn.nv, rsm_nn.nh);
    
    for(int i = 0; i <= rsm_nn.nb; i++)
    {
        fprintf(file, "%lf\n", rsm_nn.b[i]);
    }

    for(int i = 0; i <= rsm_nn.nw; i++)
    {
        fprintf(file, "%lf\n", rsm_nn.w[i]);
    }

    fclose(file);
}

RSM_t rsm_load(const char * path)
{
    FILE * const file = fopen(path, "r");
    int nv = 0;
    int nh = 0;

    fscanf(file, "%d %d\n", &nv, &nh);

    const RSM_t rsm_nn = rsm_build(nv, nh);

    for(int i = 0; i <= rsm_nn.nb; i++)
    {
        fscanf(file, "%lf\n", &rsm_nn.b[i]);
    }

    for(int i = 0; i <= rsm_nn.nw; i++)
    {
        fscanf(file, "%lf\n", &rsm_nn.w[i]);
    }
    fclose(file);
    return rsm_nn;
}

void rsm_print(const double * arr, const int size)
{

}

void rsm_free(const RSM_t rsm_nn)
{
    free(rsm_nn.w);
    free(rsm_nn.b);
    free(rsm_nn.v);
    free(rsm_nn.h);
    rsm_nn = NULL;
}