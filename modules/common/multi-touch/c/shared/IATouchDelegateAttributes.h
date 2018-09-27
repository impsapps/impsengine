//
//  IATouchDelegateAttributes.h
//  MultiTouch
//
//  Created by Konstantin on 23/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IATouchDelegateAttributes_h
#define IATouchDelegateAttributes_h

#include "IATouch.h"
#include "IAArrayList.h"

typedef struct{
    //@set+get
    void * correspondingObject;
    //@set+get
    bool (*wantToUseTouch)(void * correspondingObject, IATouch touch);
    //@set+get
    bool (*wantToConsumeTouch)(void * correspondingObject, IATouch touch);
    
    //@set+get
    void (*onTouchBegan)(void * correspondingObject, size_t numTouches, IATouch touches[numTouches]);
    //@set+get
    void (*onTouchMoved)(void * correspondingObject, size_t numTouches, IATouch touches[numTouches]);
    //@set+get
    void (*onTouchEnded)(void * correspondingObject, size_t numTouches, IATouch touches[numTouches]);
    //@set+get
    void (*onTouchCanceled)(void * correspondingObject);
    
    //@set+get
    int zOrder;
} IATouchDelegateAttributes;


void IATouchDelegateAttributes_make(IATouchDelegateAttributes *, void * correspondingObject);

void IATouchDelegateAttributes_setAlwaysWantToConsumeTouch(IATouchDelegateAttributes *, bool alwaysWantToConsumeTouch);

#include "IATouchDelegateAttributes+Generated.h"

#endif
