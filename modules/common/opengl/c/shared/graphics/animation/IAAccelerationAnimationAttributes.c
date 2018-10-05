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


