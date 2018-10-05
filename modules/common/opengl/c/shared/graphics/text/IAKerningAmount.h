#ifndef IAKerningAmount_h
#define IAKerningAmount_h

#include "IAObject.h"

typedef struct{
    //@extend
    IAObject base;
    //@get
    float amount;
} IAKerningAmount;


void IAKerningAmount_make(IAKerningAmount *, float amount);

#include "IAKerningAmount+Generated.h"

#endif
