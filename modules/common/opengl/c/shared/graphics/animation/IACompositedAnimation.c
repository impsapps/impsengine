//
//  IACompositedAnimation.c
//  Hit Verto
//
//  Created by Konstantin Merker on 24.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IACompositedAnimation.h"
#include "IAArrayListIterator.h"

#define CLASSNAME "IACompositedAnimation"


void IACompositedAnimation_drawFunction(const IACompositedAnimation * this);


void IACompositedAnimation_init(IACompositedAnimation * this){
    IADrawable_make((IADrawable *) this, (void (*)(const IADrawable*)) IACompositedAnimation_drawFunction);
    this->startTime = 0;
    this->currentTime = 0;
    IAArrayList_init(&this->delegates, 10);
#ifdef DEBUG
    IAAllocationTracker_objectAllocated(CLASSNAME);
#endif
}

void IACompositedAnimation_addAccelerationAnimation(IACompositedAnimation * this, IAAccelerationAnimation * animation){
    IACompositedAnimationDelegate * delegate = IAAccelerationAnimation_getAnimationDelegate(animation);
    IACompositedAnimation_addAnimation(this, delegate);
}

void IACompositedAnimation_addFrameAnimation(IACompositedAnimation * this, IAFrameAnimation * animation){
    IACompositedAnimationDelegate * delegate = IAFrameAnimation_getAnimationDelegate(animation);
    IACompositedAnimation_addAnimation(this, delegate);
}

void IACompositedAnimation_addPauseAnimation(IACompositedAnimation * this, IAPauseAnimation * animation){
    IACompositedAnimationDelegate * delegate = IAPauseAnimation_getAnimationDelegate(animation);
    IACompositedAnimation_addAnimation(this, delegate);
}

void IACompositedAnimation_addAnimation(IACompositedAnimation * this, IACompositedAnimationDelegate * delegate){
    IAArrayList_add(&this->delegates, delegate);
}

void IACompositedAnimation_drawFunction(const IACompositedAnimation * this){
#ifdef DEBUG
    assert(IAArrayList_isEmpty(&this->delegates) == false);
#endif
    
    uint64_t startTimeForAnimation = this->startTime;
    
    IACompositedAnimationDelegate * delegate = NULL;
    uint64_t durationOfLastAnimation = 0;
    
    foreach (delegate in arrayList(&this->delegates)){
        startTimeForAnimation += durationOfLastAnimation;
        uint64_t duration = IACompositedAnimationDelegate_getDuration(delegate);
        durationOfLastAnimation = duration;
        if (this->currentTime < startTimeForAnimation + duration) {
            break;
        }
    }
    if (delegate == NULL) {
        delegate = IAArrayList_getLast(&this->delegates);
    }
    
    IACompositedAnimationDelegate_setStartTime(delegate, startTimeForAnimation);
    IACompositedAnimationDelegate_setCurrentTime(delegate, this->currentTime);
    IACompositedAnimationDelegate_draw(delegate);
}

bool IACompositedAnimation_isAnimating(const IACompositedAnimation * this){
    if (this->currentTime < IACompositedAnimation_getFinishTime(this)) {
        return true;
    }else{
        return false;
    }
}

uint64_t IACompositedAnimation_getFinishTime(const IACompositedAnimation * this){
    uint64_t finishTime = this->startTime;
    IACompositedAnimationDelegate * delegate;
    foreach (delegate in arrayList(&this->delegates)) {
        finishTime += IACompositedAnimationDelegate_getDuration(delegate);
    }
    return finishTime;
}

void IACompositedAnimation_releaseAllAddedAnimations(IACompositedAnimation * this){
    IAArrayList_callFunctionOnAllObjects(&this->delegates, (void (*)(void *)) IACompositedAnimationDelegate_releaseCorrespondingAnimation);
}

void IACompositedAnimation_deinit(IACompositedAnimation * this){
    IAArrayList_deinit(&this->delegates);
#ifdef DEBUG
    IAAllocationTracker_objectDeallocated(CLASSNAME);
#endif
}


