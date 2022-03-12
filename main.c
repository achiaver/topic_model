#include "main.h"
#include "libs/parameters.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stdout, "./topic_model <PARAMETERS FILE>\n");
        exit(2);
    }


    PARAM_t *parameters = parameters_readin(argv[1]); 
    parameters_print(parameters);

//    RSM_t *rsm_nn = rsm_build(parameters->num_vis, parameters->num_hid, 0);

//   rsm_print(rsm_nn);
//    rsm_save(rsm_nn, parameters->weights_filename);
//    rsm_free(rsm_nn);

    RSM_t *rsm_n1 = rsm_load(parameters->weights_filename);
    rsm_print(rsm_n1);

    rsm_n1->v[0] = 3.0;
    rsm_n1->v[1] = 1.0;

    rsm_n1->h = sample_hidden_from_visible(rsm_n1);
    rsm_n1->v = sample_visible_from_hidden(rsm_n1);



    rsm_free(rsm_n1);
    parameters_delete(parameters); 
    return EXIT_SUCCESS;
}
