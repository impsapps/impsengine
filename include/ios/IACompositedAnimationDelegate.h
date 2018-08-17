//
//  IACompositedAnimationDelegate.h
//  Hit Verto
//
//  Created by Konstantin Merker on 24/09/15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IACompositedAnimationDelegate_h
#define Hit_Verto_IACompositedAnimationDelegate_h

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
