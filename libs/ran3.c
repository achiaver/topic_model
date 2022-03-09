
/*
****************************************************************************

			Random Number Generator
		      Version 1.0,  Jan. 13, 1992
		      From Numerical Recipies in C 

		Generates random number in interval [0, 1].

****************************************************************************
*/
#include "ran3.h"

#define MBIG 1000000000
#define MSEED 161803398
#define MZ 0
#define FAC (1.0/MBIG)

double ran3 (int *idum)
{
    static int inext;
    static int inextp;
    static double ma[56];
    static int iff = 0;
    long mj;
    long mk;
    int i;
    int ii;
    int k;

    if (*idum < 0 || iff == 0) 
    {
        iff = 1;
        mj = MSEED - (*idum < 0 ? -*idum : *idum);
        mj %= MBIG;
        ma[55] = mj;
        mk = 1;

        for (i = 1; i <= 54; i++)
        {
            ii = (21*i) % 55;
            ma[ii] = mk;
            mk = mj - mk;
            if (mk < MZ)
            {
                mk += MBIG;
            }
            mj = ma[ii];
        }

        for (k = 1; k <= 4; k++)
        {
            for (i = 1; i <= 55; i++)
            {
                ma[i] -= ma[1 + (i+30) % 55];
                if (ma[i] < MZ)
                {
                    ma[i] += MBIG;
                }
            }
        }

        inext = 0;
        inextp = 31;
        *idum = 1;
    }

    if (++inext == 56)
    {
        inext = 1;
    }
    if (++inextp == 56) 
    {
        inextp = 1;
    }

    mj = ma[inext] - ma[inextp];
    if (mj < MZ)
    {
        mj += MBIG;
    }

    ma[inext] = mj;
    return mj * FAC;
}

double rand_act (int *iseed)
{
    return (int) (ran3(iseed) + 0.5);
}


double rand_1 (int *iseed)
{
    return ran3(iseed);
}


double rand_range (int *iseed, double min, double max)
{
    return ((max - min) * ran3(iseed) + min);
}


#undef MBIG
#undef MSEED
#undef MZ
#undef FAC
