//
//  IAAccelerationAnimationAttributes.h
//  OpenGL
//
//  Created by Konstantin Merker on 01/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAccelerationAnimationAttributes_h
#define IAAccelerationAnimationAttributes_h

#include <stdint.h>
#include "IADrawableRect.h"

typedef struct{
    //@get
    IADrawableRect * drawableRectToAnimate;
    //@set+get
    float (*accelerationFunction)(float, float, float);
    //@get
    uint64_t duration;
} IAAccelerationAnimationAttributes;


void IAAccelerationAnimationAttributes_make(IAAccelerationAnimationAttributes *, IADrawableRect * drawableRectToAnimate, uint64_t duration);

#include "IAAccelerationAnimationAttributes+Generated.h"

#endif
