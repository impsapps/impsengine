#include "IALibrary.h"
#include "IACompositedAnimationDelegate.h"

#define CLASSNAME "IACompositedAnimationDelegate"


void IACompositedAnimationDelegate_make(IACompositedAnimationDelegate * this, IACompositedAnimationDelegateAttributes * attributes){
    *this = (IACompositedAnimationDelegate){
        .correspondingAnimation = IACompositedAnimationDelegateAttributes_getCorrespondingAnimation(attributes),
        .setStartTime = IACompositedAnimationDelegateAttributes_getSetStartTimeFunction(attributes),
        .setCurrentTime = IACompositedAnimationDelegateAttributes_getSetCurrentTimeFunction(attributes),
        .getDuration = IACompositedAnimationDelegateAttributes_getGetDurationFunction(attributes),
        .releaseCorrespondingAnimation = IACompositedAnimationDelegateAttributes_getReleaseCorrespondingAnimationFunction(attributes)
    };
}

void IACompositedAnimationDelegate_draw(const IACompositedAnimationDelegate * this){
    IADrawable_draw(this->correspondingAnimation);
}

