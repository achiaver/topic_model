#include "random_lib.h"

void random_seed (int nondeterministic_seed)
{
    int address_1 = 42;
    int address_2 = 4200;
    if (nondeterministic_seed)
    {
        pcg32_srandom(time(NULL) ^ (intptr_t)&address_1, (intptr_t)&address_2);
    } 
    else
    {
        pcg32_srandom((uint64_t)address_1, (uint64_t)address_2);
    }
}

int random_bound (int bound)
{
    return pcg32_boundedrand(bound);
}


double random_activ (void)
{
    return (double)pcg32_boundedrand(2);
}


double random_1 (void)
{
    return ldexp(pcg32_random(), -32);
}


double random_range (double min, double max)
{
    double random = (double) pcg32_random()/ ((double)UINT32_MAX + 1);
    return ((max - min) * random + min);
}
