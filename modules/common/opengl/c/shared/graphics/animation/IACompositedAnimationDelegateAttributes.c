//
//  IACompositedAnimationDelegateAttributes.c
//  OpenGL
//
//  Created by Konstantin Merker on 28/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

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


