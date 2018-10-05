#ifndef IAPauseAnimation_h
#define IAPauseAnimation_h

#include "IADrawableRect.h"
#include "IACompositedAnimationDelegate.h"

typedef struct{
    //@extend
	IADrawableRect drawable;
    IADrawableRect * drawableRectToAnimate;
    //@get
    uint64_t duration;
    
    //@getAsRef
    IACompositedAnimationDelegate animationDelegate;
} IAPauseAnimation;


void IAPauseAnimation_make(IAPauseAnimation *, IADrawableRect * drawableRectToAnimate, uint64_t duration);

#include "IAPauseAnimation+Generated.h"

#endif
