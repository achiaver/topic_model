#include "rsm.h"

double sigmoid(const double x) 
{
    sig = 1 / (1 + exp(-x));
    return sig;
}


RSM_t rsm_build(const int nvis, const int nhid)
{
    RSM_t rsm_nn;
    rsm_nn.nb = nvis + nhid;
    rsm_nn.nw = nvis * nhid;
    rsm_nn.nv = nvis;
    rsm_nn.nh = nhid;
    rsm_nn.w = (double *) calloc(rsm_nn.nw, sizeof(*rsm_nn.w));
    rsm_nn.b = (double *) calloc(rsm_nn.nb, sizeof(*rsm_nn.b));
    rsm_nn.v = (int *) calloc(rsm_nn.nv, sizeof(*rsm_nn.v));
    rsm_nn.h = (int *) calloc(rsm_nn.nh, sizeof(rsm_nn.h));
    
    return rsm_nn;
}

void rsm_save(const RSM_t rsm_nn, const char * path)
{

}

RSM_t rsm_load(const char * path)
{

}

void rsm_print(const double * arr, const int size)
{

}

void rsm_free(const RSM_t rsm_nn)
{

}