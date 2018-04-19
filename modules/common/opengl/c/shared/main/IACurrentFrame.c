//
//  IACurrentFrame.c
//  OpenGL
//
//  Created by Konstantin Merker on 30.08.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IACurrentFrame.h"
#include "IACurrentFrame+Private.h"

static uint64_t currentTimeForFrame = 0;

void IACurrentFrame_setTime(uint64_t currentTimeForFrameTemp){
    currentTimeForFrame = currentTimeForFrameTemp;
}

uint64_t IACurrentFrame_getTime(){
    return currentTimeForFrame;
}

