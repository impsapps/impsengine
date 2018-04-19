//
//  IACompositedAnimationDelegate.c
//  Hit Verto
//
//  Created by Konstantin Merker on 24/09/15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

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

