typedef struct rsm
{
    double *w;
    double *b;
    int *v;
    int *h;
    int nw;
    int nb;
    int nv;
    int nh;
} RSM_t;

RSM_t rsm_build(const int nv, const int nh);
void rsm_save(const RSM_t rsm_nn, const char * path);
RSM_t rsm_load(const char * path);
void rsm_print(const double * arr, const int size);
void rsm_free(const RSM_t rsm_nn);

int * rsm_train(const RSM_t rsm_nn, const int * in);
int * rsm_model(const RSM_t rsm_nn, const int * in);
