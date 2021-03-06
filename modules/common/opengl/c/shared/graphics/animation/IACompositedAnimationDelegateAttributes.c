#include "IALibrary.h"
#include "IACompositedAnimationDelegateAttributes.h"

#define CLASSNAME "IACompositedAnimationDelegateAttributes"


void IACompositedAnimationDelegateAttributes_make(IACompositedAnimationDelegateAttributes * this, IADrawable * correspondingAnimation, uint64_t (*getDuration)(IADrawable * correspondingAnimation), void (*releaseCorrespondingAnimation)(IADrawable * correspondingAnimation)){
    *this = (IACompositedAnimationDelegateAttributes){
        .correspondingAnimation = correspondingAnimation,
        .getDuration = getDuration,
        .releaseCorrespondingAnimation = releaseCorrespondingAnimation
    };
}


