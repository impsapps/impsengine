#ifndef IACompositedAnimationDelegateAttributes_h
#define IACompositedAnimationDelegateAttributes_h

#include <stdint.h>
#include "IADrawable.h"

typedef struct{
    //@get
    IADrawable * correspondingAnimation;
    //@set+get
    void (*setStartTime)(IADrawable * correspondingAnimation, uint64_t startTime);
    //@set+get
    void (*setCurrentTime)(IADrawable * correspondingAnimation, uint64_t currentTime);
    //@get
    uint64_t (*getDuration)(IADrawable * correspondingAnimation);
    //@get
    void (*releaseCorrespondingAnimation)(IADrawable * correspondingAnimation);
} IACompositedAnimationDelegateAttributes;


void IACompositedAnimationDelegateAttributes_make(IACompositedAnimationDelegateAttributes *, IADrawable * correspondingAnimation, uint64_t (*getDuration)(IADrawable * correspondingAnimation), void (*releaseCorrespondingAnimation)(IADrawable * correspondingAnimation));

#include "IACompositedAnimationDelegateAttributes+Generated.h"

#endif
