#ifndef IAAccelerationAnimation_h
#define IAAccelerationAnimation_h

#include "IAAccelerationAnimationAttributes.h"
#include "IACompositedAnimationDelegate.h"

typedef struct{
    //@extend
    IADrawable drawable;
    IADrawableRect * drawableRectToAnimate;
    float (*accelerationFunction)(float, float, float);
    //@get
    uint64_t duration;
    
    //@set
    IARect startRect;
    //@set
    IARect goalRect;
    //@set+get
    uint64_t startTime;
    //@set
    uint64_t currentTime;
    
    //@getAsRef
    IACompositedAnimationDelegate animationDelegate;
} IAAccelerationAnimation;


void IAAccelerationAnimation_make(IAAccelerationAnimation *, IAAccelerationAnimationAttributes * animationAttributes);
void IAAccelerationAnimation_makeCopy(IAAccelerationAnimation *, const IAAccelerationAnimation * animationToCopy);

#include "IAAccelerationAnimation+Generated.h"

#endif
