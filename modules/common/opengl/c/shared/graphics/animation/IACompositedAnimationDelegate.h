#ifndef IACompositedAnimationDelegate_h
#define IACompositedAnimationDelegate_h

#include "IACompositedAnimationDelegateAttributes.h"

typedef struct{
    IADrawable * correspondingAnimation;
    //@exe
    void (*setStartTime)(IADrawable * correspondingAnimation, uint64_t startTime);
    //@exe
    void (*setCurrentTime)(IADrawable * correspondingAnimation, uint64_t currentTime);
    //@exe
    uint64_t (*getDuration)(IADrawable * correspondingAnimation);
    //@exe
    void (*releaseCorrespondingAnimation)(IADrawable * correspondingAnimation);
} IACompositedAnimationDelegate;


void IACompositedAnimationDelegate_make(IACompositedAnimationDelegate *, IACompositedAnimationDelegateAttributes * attributes);

void IACompositedAnimationDelegate_draw(const IACompositedAnimationDelegate *);

#include "IACompositedAnimationDelegate+Generated.h"

#endif
