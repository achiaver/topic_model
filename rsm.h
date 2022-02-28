typedef struct rsm
{
    double *w;  // weights array
    double *b;  // biases array
    int *v;     // visible layer 
    int *h;     // hidden layer
    int nw;     // number of weights 
    int nb;     // number of biases
    int nv;     // number of visible units
    int nh;     // number of hidden units
} RSM_t;

RSM_t rsm_build(const int nv, const int nh);
void rsm_save(const RSM_t rsm_nn, const char * path);
RSM_t rsm_load(const char * path);
void rsm_print(const double * arr, const int size);
void rsm_free(const RSM_t rsm_nn);

int * rsm_train(const RSM_t rsm_nn, const int * in);
int * rsm_predict(const RSM_t rsm_nn, const int * in);
