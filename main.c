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

    RSM_t *rsm_nn = rsm_build(parameters->num_vis, parameters->num_hid, 0);


    rsm_print(rsm_nn);
    rsm_free(rsm_nn);

    return EXIT_SUCCESS;
}
