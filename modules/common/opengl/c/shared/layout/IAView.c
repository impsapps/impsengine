//
//  IAView.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 28.06.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAView.h"
#include <string.h>

#define CLASSNAME "IAView"


void IAView_make(IAView * this, const char * viewName, const IAViewAttributes * attributes){
    *this = (IAView){
        .correspondingView = IAViewAttributes_getCorrespondingView(attributes),
        .setArgs = IAViewAttributes_getSetArgsFunction(attributes),
        .onFadeInStart = IAViewAttributes_getOnFadeInStartFunction(attributes),
        .drawFadeIn = IAViewAttributes_getDrawFadeInFunction(attributes),
        .onFadeInFinished = IAViewAttributes_getOnFadeInFinishedFunction(attributes),
        .draw = IAViewAttributes_getDrawFunction(attributes),
        .onFadeOutStart = IAViewAttributes_getOnFadeOutStartFunction(attributes),
        .drawFadeOut = IAViewAttributes_getDrawFadeOutFunction(attributes),
        .onFadeOutFinished = IAViewAttributes_getOnFadeOutFinishedFunction(attributes),
        .zOrder = IAViewAttributes_getZOrder(attributes)
    };
    strncpy(this->viewName, viewName, 20);
    this->viewName[20] = '\0';
}

bool IAView_isIdle(const IAView * this){
    if (this->isShown == false && this->isFadingIn == false && this->isFadingOut == false) {
        return true;
    }else{
        return false;
    }
}

void IAView_setArgs(const IAView * this, const void * args){
    debugAssert(this->isShown == false);
    debugAssert(this->isFadingIn == false);
    debugAssert(this->isFadingOut == false);
    if (this->setArgs != NULL){
        this->setArgs(this->correspondingView, args);
    }
}

void IAView_onFadeInStart(IAView * this, uint64_t startTime, uint64_t duration){
    debugAssert(this->isShown == false);
    debugAssert(this->isFadingIn == false);
    debugAssert(this->isFadingOut == false);
    this->isFadingIn = true;
    if (this->onFadeInStart != NULL){
        this->onFadeInStart(this->correspondingView, startTime, duration);
    }
}

void IAView_drawFadeIn(IAView * this, uint64_t startTime, uint64_t duration, uint64_t currentTime){
    debugAssert(this->isShown == false);
    debugAssert(this->isFadingIn == true);
    debugAssert(this->isFadingOut == false);
    if (this->drawFadeIn != NULL){
        this->drawFadeIn(this->correspondingView, startTime, duration, currentTime);
    }
}

void IAView_onFadeInFinished(IAView * this, uint64_t startTime, uint64_t duration, uint64_t endTime){
    debugAssert(this->isShown == false);
    debugAssert(this->isFadingIn == true);
    debugAssert(this->isFadingOut == false);
    this->isShown = true;
    this->isFadingIn = false;
    if (this->onFadeInFinished != NULL){
        this->onFadeInFinished(this->correspondingView, startTime, duration, endTime);
    }
}

void IAView_draw(IAView * this, uint64_t currentTime){
    debugAssert(this->isShown == true);
    debugAssert(this->isFadingIn == false);
    debugAssert(this->isFadingOut == false);
    if (this->draw != NULL){
        this->draw(this->correspondingView, currentTime);
    }
}

void IAView_onFadeOutStart(IAView * this, uint64_t startTime, uint64_t duration){
    debugAssert(this->isShown == true);
    debugAssert(this->isFadingIn == false);
    debugAssert(this->isFadingOut == false);
    this->isShown = false;
    this->isFadingOut = true;
    if (this->onFadeOutStart != NULL){
        this->onFadeOutStart(this->correspondingView, startTime, duration);
    }
}

void IAView_drawFadeOut(IAView * this, uint64_t startTime, uint64_t duration, uint64_t currentTime){
    debugAssert(this->isShown == false);
    debugAssert(this->isFadingIn == false);
    debugAssert(this->isFadingOut == true);
    if (this->drawFadeOut != NULL){
        this->drawFadeOut(this->correspondingView, startTime, duration, currentTime);
    }
}

void IAView_onFadeOutFinished(IAView * this, uint64_t startTime, uint64_t duration, uint64_t endTime){
    debugAssert(this->isShown == false);
    debugAssert(this->isFadingIn == false);
    debugAssert(this->isFadingOut == true);
    this->isFadingOut = false;
    if (this->onFadeOutFinished != NULL){
        this->onFadeOutFinished(this->correspondingView, startTime, duration, endTime);
    }
}

