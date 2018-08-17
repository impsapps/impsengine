//
//  IACompositedAnimation.h
//  Hit Verto
//
//  Created by Konstantin Merker on 24.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IACompositedAnimation_h
#define Hit_Verto_IACompositedAnimation_h

#include "IADrawableRect.h"
#include "IARect.h"
#include "IAArrayList.h"
#include "IACompositedAnimationDelegate.h"
#include "IAAccelerationAnimation.h"
#include "IAFrameAnimation.h"
#include "IAPauseAnimation.h"

typedef struct{
    //@extend
    IADrawable drawable;
    IAArrayList delegates;
    
    //@set+get
    uint64_t startTime;
    //@set
    uint64_t currentTime;
} IACompositedAnimation;


void IACompositedAnimation_init(IACompositedAnimation *);

void IACompositedAnimation_addAccelerationAnimation(IACompositedAnimation *, IAAccelerationAnimation * animation);
void IACompositedAnimation_addFrameAnimation(IACompositedAnimation *, IAFrameAnimation * animation);
void IACompositedAnimation_addPauseAnimation(IACompositedAnimation *, IAPauseAnimation * animation);

void IACompositedAnimation_addAnimation(IACompositedAnimation *, IACompositedAnimationDelegate * delegate);

bool IACompositedAnimation_isAnimating(const IACompositedAnimation *);
uint64_t IACompositedAnimation_getFinishTime(const IACompositedAnimation *);

void IACompositedAnimation_releaseAllAddedAnimations(IACompositedAnimation *);
void IACompositedAnimation_deinit(IACompositedAnimation *);

#include "IACompositedAnimation+Generated.h"

#endif
