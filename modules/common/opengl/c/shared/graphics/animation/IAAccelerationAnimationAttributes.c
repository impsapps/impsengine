//
//  IAAccelerationAnimationAttributes.c
//  OpenGL
//
//  Created by Konstantin Merker on 01/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAAccelerationAnimationAttributes.h"
#include "IAAcceleration.h"

#define CLASSNAME "IAAccelerationAnimationAttributes"


void IAAccelerationAnimationAttributes_make(IAAccelerationAnimationAttributes * this, IADrawableRect * drawableRectToAnimate, uint64_t duration){
    *this = (IAAccelerationAnimationAttributes){
        .drawableRectToAnimate = drawableRectToAnimate,
        .accelerationFunction = IAAcceleration_linearMovementFunction,
        .duration = duration
    };
}


