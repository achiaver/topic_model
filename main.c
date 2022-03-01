#include <stdio.h>
#include <stdlib.h>
#include <include/parameters.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stdout, "./topic_model <PARAMETERS FILE>");
        exit(2);
    }

//    fprintf(stdout, "Hello,\n");
//    fprintf(stdout, "Tests...\n");

    PARAM_t *parameters = parameters_readin(argv[1]); 
    parameters_print(parameters);

    return EXIT_SUCCESS;
}