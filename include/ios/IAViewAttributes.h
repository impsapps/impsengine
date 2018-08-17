//
//  IAViewAttributes.h
//  OpenGL
//
//  Created by Konstantin Merker on 28/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAViewAttributes_h
#define IAViewAttributes_h

#include <stdint.h>

typedef struct{
    //@get
    void * correspondingView;
    //@set+get
    void (*setArgs)(void * correspondingView, const void * args);
    //@set+get
    void (*onFadeInStart)(void * correspondingView, uint64_t startTime, uint64_t duration);
    //@set+get
    void (*drawFadeIn)(void * correspondingView, uint64_t startTime, uint64_t duration, uint64_t currentTime);
    //@set+get
    void (*onFadeInFinished)(void * correspondingView, uint64_t startTime, uint64_t duration, uint64_t endTime);
    //@set+get
    void (*draw)(void * correspondingView, uint64_t currentTime);
    //@set+get
    void (*onFadeOutStart)(void * correspondingView, uint64_t startTime, uint64_t duration);
    //@set+get
    void (*drawFadeOut)(void * correspondingView, uint64_t startTime, uint64_t duration, uint64_t currentTime);
    //@set+get
    void (*onFadeOutFinished)(void *correspondingView, uint64_t startTime, uint64_t duration, uint64_t endTime);
    //@set+get
    int zOrder;
} IAViewAttributes;


void IAViewAttributes_make(IAViewAttributes *, void * correspondingView);

#include "IAViewAttributes+Generated.h"

#endif
