//
//  IACurrentFrame.c
//  OpenGL
//
//  Created by Konstantin Merker on 30.08.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IACurrentFrame.h"
#include "IACurrentFrame+Private.h"

static uint64_t currentTimeForFrame = 0;
static uint64_t deltaTimeSinceLastFrame = 0;

void IACurrentFrame_setTime(uint64_t newTime){
    debugAssert(newTime >= currentTimeForFrame && "Time must be monotonic increasing");
    static bool wasSet = false;
    if (wasSet == true) {
        deltaTimeSinceLastFrame = newTime - currentTimeForFrame;
    }
    currentTimeForFrame = newTime;
    wasSet = true;
}

uint64_t IACurrentFrame_getTime(){
    return currentTimeForFrame;
}

uint64_t IACurrentFrame_getDeltaTimeSinceLastFrame(){
    return deltaTimeSinceLastFrame;
}

