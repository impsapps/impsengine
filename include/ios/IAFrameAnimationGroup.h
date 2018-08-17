//
//  IAFrameAnimationGroup.h
//  OpenGL
//
//  Created by Konstantin Merker on 11/11/17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAFrameAnimationGroup_h
#define IAFrameAnimationGroup_h

#include "IADrawableRect.h"
#include "IAArray.h"
#include "IAFrameAnimation.h"
#include "IAFrameAnimationGroupAttributes.h"

typedef struct{
    //@extend
    IADrawableRect drawableRect;
    //@getAsConstRef
    IAArray frameAnimations;
} IAFrameAnimationGroup;


void IAFrameAnimationGroup_init(IAFrameAnimationGroup *, const IAFrameAnimationGroupAttributes * attr);

void IAFrameAnimationGroup_setStartTime(IAFrameAnimationGroup *, uint64_t startTime);
void IAFrameAnimationGroup_setCurrentTime(IAFrameAnimationGroup *, uint64_t currentTime);
void IAFrameAnimationGroup_stop(IAFrameAnimationGroup *);

void IAFrameAnimationGroup_drawFrame(const IAFrameAnimationGroup *, size_t frame);

IAFrameAnimation * IAFrameAnimationGroup_getFrameAnimation(IAFrameAnimationGroup *, size_t index);

void IAFrameAnimationGroup_deinit(IAFrameAnimationGroup *);

#include "IAFrameAnimationGroup+Generated.h"

#endif
