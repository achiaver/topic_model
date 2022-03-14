/*
 * From PCG RANDOM
 * www.pcg-random.org
 *
 * */
#ifndef __RANDOM_LIB_H__
#define __RANDOM_LIB_H__

#include <stdint.h>
#include <time.h>
#include <math.h>
#include "pcg_basic.h"

void   random_seed  (int nondeterministic_seed);
int    random_bound (int bound);
double random_activ ();
double random_1     ();
double random_range (double min, double max);


#endif /* __RANDOM_LIB_H__*/


