//
//  IAKerningAmount.h
//  OpenGL
//
//  Created by Konstantin Merker on 01.08.18.
//Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

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
