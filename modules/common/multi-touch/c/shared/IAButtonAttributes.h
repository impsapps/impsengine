//
//  IAButtonAttributes.h
//  MultiTouch
//
//  Created by Konstantin on 23/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAButtonAttributes_h
#define IAButtonAttributes_h

#include "IAImage.h"

typedef struct IAButton IAButton;

typedef struct{
    //@set+get
    IADrawableRect * normal;
    //@set+get
    IADrawableRect * touched;
    
    //@set+get
    IARect rect;
    
    //@set+get
    float rectExtensionForTouchBeganLeft;
    //@set+get
    float rectExtensionForTouchBeganTop;
    //@set+get
    float rectExtensionForTouchBeganRight;
    //@set+get
    float rectExtensionForTouchBeganBottom;
    
    //@set+get
    float rectExtensionForTouchMovedOutsideLeft;
    //@set+get
    float rectExtensionForTouchMovedOutsideTop;
    //@set+get
    float rectExtensionForTouchMovedOutsideRight;
    //@set+get
    float rectExtensionForTouchMovedOutsideBottom;
    
    //@get
    void * correspondingObject;
    //@set+get
    void(*onClick)(void * correspondingObject, IAButton * button);
    //@set+get
    void(*onIsTouchedChanged)(void * correspondingObject, IAButton * button, bool isTouched);
    
    //@set+get
    int zOrder;
    
    //@set+get
    int tag;
} IAButtonAttributes;


void IAButtonAttributes_make(IAButtonAttributes *, void * correspondingObject);

void IAButtonAttributes_setRectExtensionForTouchBegan(IAButtonAttributes *, float extension);
void IAButtonAttributes_setRectExtensionForTouchMovedOutside(IAButtonAttributes *, float extension);

#include "IAButtonAttributes+Generated.h"

#endif
