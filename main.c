#include "main.h"
#include "libs/parameters.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stdout, "./topic_model <PARAMETERS FILE>\n");
        exit(2);
    }
    random_seed(0);


    PARAM_t *parameters = parameters_readin(argv[1]); 
    parameters_print(parameters);

//    char *dataset_path = argv[2];    

//    DATA_t *dataset = data_readin(dataset_path);
//    data_dump(dataset);
//    RSM_t *rsm_nn = rsm_build(parameters->num_vis, parameters->num_hid, 0);

//    rsm_print(rsm_nn);
//    rsm_save(rsm_nn, parameters->weights_filename);
//    rsm_free(rsm_nn);

    RSM_t *rsm_n1 = rsm_load(parameters->weights_filename);
    rsm_print(rsm_n1);

    rsm_n1->v[0] = 3.0;
    rsm_n1->v[1] = 1.0;

    rsm_n1->h = sample_hidden_from_visible(rsm_n1);
    rsm_n1->v = sample_visible_from_hidden(rsm_n1);

    double *h = calloc(rsm_n1->nh, sizeof(*h));
    double *t = calloc(rsm_n1->nh, sizeof(*t));
    double *y = calloc(rsm_n1->nh, sizeof(*y));
    fprintf(stdout, "Coping hidden values\n");
    
    h = rsm_n1->h;
    fprintf(stdout, "h = rsm_n1->h\n");
    for (int i = 0; i < rsm_n1->nh; i++)
    {
        fprintf(stdout, "%lf\t", rsm_n1->h[i]);
    }
    fprintf(stdout, "\n");  

    for (int i = 0; i < rsm_n1->nh; i++)
    {
        fprintf(stdout, "%lf\t", h[i]);
    }   
    fprintf(stdout, "\n");

    rsm_n1->h[0] = 4;
    fprintf(stdout, "rsm_n1->h[0] = 4\n");
    for (int i = 0; i < rsm_n1->nh; i++)
    {
        fprintf(stdout, "%lf\t", rsm_n1->h[i]);
    }
    fprintf(stdout, "\n");  

    for (int i = 0; i < rsm_n1->nh; i++)
    {
        fprintf(stdout, "%lf\t", h[i]);
    }   
    fprintf(stdout, "\n");

    *t = *rsm_n1->h;
    fprintf(stdout, "*t = *rsm_n1->h\n");
    for (int i = 0; i < rsm_n1->nh; i++)
    {
        fprintf(stdout, "%lf\t", rsm_n1->h[i]);
    }
    fprintf(stdout, "\n");  

    for (int i = 0; i < rsm_n1->nh; i++)
    {
        fprintf(stdout, "%lf\t", t[i]);
    }   
    fprintf(stdout, "\n");

    rsm_n1->h[0] = 22.5; 
    fprintf(stdout, "rsm_n1->h[0] = 22.5\n");
    for (int i = 0; i < rsm_n1->nh; i++)
    {
        fprintf(stdout, "%lf\t", rsm_n1->h[i]);
    }
    fprintf(stdout, "\n");  

    for (int i = 0; i < rsm_n1->nh; i++)
    {
        fprintf(stdout, "%lf\t", t[i]);
    }   
    fprintf(stdout, "\n");

    memcpy(y, rsm_n1->h, sizeof(*y) * rsm_n1->nh);
    fprintf(stdout, "memcpy(y, rsm_n1->h, sizeof(*y) * rsm_n1->nh)\n");
    for (int i = 0; i < rsm_n1->nh; i++)
    {
        fprintf(stdout, "%lf\t", rsm_n1->h[i]);
    }
    fprintf(stdout, "\n");  

    for (int i = 0; i < rsm_n1->nh; i++)
    {
        fprintf(stdout, "%lf\t", y[i]);
    }   
    fprintf(stdout, "\n");

    rsm_n1->h[0] = 42; 
    fprintf(stdout, "rsm_n1->h[0] = 42\n");
    for (int i = 0; i < rsm_n1->nh; i++)
    {
        fprintf(stdout, "%lf\t", rsm_n1->h[i]);
    }
    fprintf(stdout, "\n");  

    for (int i = 0; i < rsm_n1->nh; i++)
    {
        fprintf(stdout, "%lf\t", y[i]);
    }   
    fprintf(stdout, "\n");



    rsm_free(rsm_n1);
    parameters_delete(parameters); 
//    data_free(dataset); 
    free(h);
    free(t);
    free(y);
    return EXIT_SUCCESS;
}
