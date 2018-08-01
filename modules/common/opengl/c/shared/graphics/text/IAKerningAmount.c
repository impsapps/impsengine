//
//  IAKerningAmount.c
//  OpenGL
//
//  Created by Konstantin Merker on 01.08.18.
//Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAKerningAmount.h"

#define CLASSNAME "IAKerningAmount"


void IAKerningAmount_make(IAKerningAmount * this, float amount){
    debugAssert(amount >= 0 && "kerning amounts must be positive");
    *this = (IAKerningAmount){
        .base = IAObject_make(this),
        .amount = amount
    };
}


