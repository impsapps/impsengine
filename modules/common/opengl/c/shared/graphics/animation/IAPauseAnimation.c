//
//  IAPauseAnimation.c
//  OpenGL
//
//  Created by Konstantin Merker on 30/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAPauseAnimation.h"

#define CLASSNAME "IAPauseAnimation"


void IAPauseAnimation_drawFunction(const IAPauseAnimation * this);
void IAPauseAnimation_setRectFunction(IAPauseAnimation * this, IARect rect);

void IAPauseAnimation_make(IAPauseAnimation * this, IADrawableRect * drawableRectToAnimate, uint64_t duration){
    IADrawableRect_make((IADrawableRect *) this, (void (*)(const IADrawable *)) IAPauseAnimation_drawFunction, (void (*)(IADrawableRect *, IARect)) IAPauseAnimation_setRectFunction, NULL);
    this->drawableRectToAnimate = drawableRectToAnimate;
    this->duration = duration;
    
    IACompositedAnimationDelegateAttributes attributes;
    IACompositedAnimationDelegateAttributes_make(&attributes, (IADrawable *) this, (uint64_t (*)(IADrawable *)) IAPauseAnimation_getDuration, (void (*)(IADrawable *)) IAPauseAnimation_release);
    IACompositedAnimationDelegate_make(&this->animationDelegate, &attributes);
}

void IAPauseAnimation_drawFunction(const IAPauseAnimation * this){
    IARect rect = IAPauseAnimation_getRect(this);
    IADrawableRect_setRect(this->drawableRectToAnimate, rect);
    IADrawableRect_draw(this->drawableRectToAnimate);
}

void IAPauseAnimation_setRectFunction(IAPauseAnimation * this, IARect rect){
}

