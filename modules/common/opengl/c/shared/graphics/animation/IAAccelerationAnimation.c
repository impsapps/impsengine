#include "IALibrary.h"
#include "IAAccelerationAnimation.h"
#include "IAAcceleration.h"

#define CLASSNAME "IAAccelerationAnimation"


void IAAccelerationAnimation_drawFunction(const IAAccelerationAnimation * this);


void IAAccelerationAnimation_make(IAAccelerationAnimation * this, IAAccelerationAnimationAttributes * animationAttributes){
    IADrawable_make((IADrawable *) this, (void (*)(const IADrawable *)) IAAccelerationAnimation_drawFunction);
    this->drawableRectToAnimate = IAAccelerationAnimationAttributes_getDrawableRectToAnimate(animationAttributes);
    this->accelerationFunction = IAAccelerationAnimationAttributes_getAccelerationFunctionFunction(animationAttributes);
    this->duration = IAAccelerationAnimationAttributes_getDuration(animationAttributes);
    
    this->startRect = IARect_make(0.0f, 0.0f, 100.0f, 100.0f);
    this->goalRect = IARect_make(100.0f, 0.0f, 100.0f, 100.0f);
    this->startTime = 0;
    this->currentTime = 0;
    
    IACompositedAnimationDelegateAttributes delegateAttributes;
    IACompositedAnimationDelegateAttributes_make(&delegateAttributes, (IADrawable *) this, (uint64_t (*)(IADrawable *)) IAAccelerationAnimation_getDuration, (void (*)(IADrawable *)) IAAccelerationAnimation_release);
    IACompositedAnimationDelegateAttributes_setSetStartTimeFunction(&delegateAttributes, (void (*)(IADrawable *, uint64_t)) IAAccelerationAnimation_setStartTime);
    IACompositedAnimationDelegateAttributes_setSetCurrentTimeFunction(&delegateAttributes, (void (*)(IADrawable *, uint64_t)) IAAccelerationAnimation_setCurrentTime);
    IACompositedAnimationDelegate_make(&this->animationDelegate, &delegateAttributes);
}

void IAAccelerationAnimation_makeCopy(IAAccelerationAnimation * this, const IAAccelerationAnimation * animationToCopy){
    *this = *animationToCopy;
}

void IAAccelerationAnimation_drawFunction(const IAAccelerationAnimation * this){
    float progress = IAAcceleration_calculateProgress(this->startTime, this->currentTime, this->duration);
    IARect currentRect = IAAcceleration_calculateCurrentRect(this->startRect, this->goalRect, progress, this->accelerationFunction);
    IADrawableRect_setRect(this->drawableRectToAnimate, currentRect);
    IADrawableRect_draw(this->drawableRectToAnimate);
}


