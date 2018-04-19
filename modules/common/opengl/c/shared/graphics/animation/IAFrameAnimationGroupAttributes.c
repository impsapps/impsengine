//
//  IAFrameAnimationGroupAttributes.c
//  OpenGL
//
//  Created by Konstantin Merker on 30/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAFrameAnimationGroupAttributes.h"
#include "IAAllocationTracker.h"

#define CLASSNAME "IAFrameAnimationGroupAttributes"


static void IAFrameAnimationGroupAttributes_createNamesArray(IAFrameAnimationGroupAttributes * this, size_t numberOfAnimations, const char * names[numberOfAnimations]);
static void IAFrameAnimationGroupAttributes_destroyNamesArray(IAFrameAnimationGroupAttributes * this);


void IAFrameAnimationGroupAttributes_init(IAFrameAnimationGroupAttributes * this, IAImageContext * imageContext, size_t numberOfAnimations, const char * names[numberOfAnimations], int numberOfFrames, uint64_t duration){
    *this = (IAFrameAnimationGroupAttributes){
        .imageContext = imageContext,
        .numberOfFrames = numberOfFrames,
        .duration = duration
    };
    IAFrameAnimationGroupAttributes_createNamesArray(this, numberOfAnimations, names);
    IA_increaseAllocationCount();
}

void IAFrameAnimationGroupAttributes_initWithDurationOfSingleFrame(IAFrameAnimationGroupAttributes * this, IAImageContext * imageContext, size_t numberOfAnimations, const char * names[numberOfAnimations], int numberOfFrames, uint64_t durationOfSingleFrame){
    IAFrameAnimationGroupAttributes_init(this, imageContext, numberOfAnimations, names, numberOfFrames, durationOfSingleFrame * numberOfFrames);
}

void IAFrameAnimationGroupAttributes_setNames(IAFrameAnimationGroupAttributes * this, size_t numberOfAnimations, const char * names[numberOfAnimations]){
    IAFrameAnimationGroupAttributes_destroyNamesArray(this);
    IAFrameAnimationGroupAttributes_createNamesArray(this, numberOfAnimations, names);
}

const char * IAFrameAnimationGroupAttributes_getName(const IAFrameAnimationGroupAttributes * this, size_t index){
    IAString * name = IAArray_get(&this->names, index);
    return IAString_toCharArray(name);
}

size_t IAFrameAnimationGroupAttributes_getNumberOfAnimations(const IAFrameAnimationGroupAttributes * this){
    return IAArray_getSize(&this->names);
}

static void IAFrameAnimationGroupAttributes_createNamesArray(IAFrameAnimationGroupAttributes * this, size_t numberOfAnimations, const char * names[numberOfAnimations]){
    IAArray_init(&this->names, numberOfAnimations);
    for (size_t i = 0; i < numberOfAnimations; i++) {
        IAString * name = IAString_new(names[i]);
        IAArray_set(&this->names, i, name);
    }
}

static void IAFrameAnimationGroupAttributes_destroyNamesArray(IAFrameAnimationGroupAttributes * this){
    IAArray_callFunctionOnAllObjects(&this->names, (void (*)(void *)) IAString_release);
    IAArray_deinit(&this->names);
}

void IAFrameAnimationGroupAttributes_deinit(IAFrameAnimationGroupAttributes * this){
    IAFrameAnimationGroupAttributes_destroyNamesArray(this);
    IA_decreaseAllocationCount();
}
