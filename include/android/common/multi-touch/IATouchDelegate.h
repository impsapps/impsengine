//
//  IATouchDelegate.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 28.05.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IATouchDelegate_h
#define ImpsEngineiOS_IATouchDelegate_h

#include "IAArrayList.h"
#include "IATouch.h"
#include "IATouchDelegateAttributes.h"
#include <stdbool.h>

typedef struct{
    void * correspondingObject;
    //@exe
    bool (*wantToUseTouch)(void * correspondingObject, IATouch * touch);
    //@exe
    bool (*wantToConsumeTouch)(void * correspondingObject, IATouch * touch);
    
    void (*touchBegan)(void * correspondingObject, IAArrayList * touches);
    void (*touchMoved)(void * correspondingObject, IAArrayList * touches);
    void (*touchEnded)(void * correspondingObject, IAArrayList * touches);
    void (*touchCanceled)(void * correspondingObject);
    IAArrayList touchesForTouchEvent;
    
    //@get
    int zOrder;
} IATouchDelegate;


void IATouchDelegate_init(IATouchDelegate *, const IATouchDelegateAttributes * attr);

void IATouchDelegate_addTouchToTouchEvent(IATouchDelegate *, IATouch * touch);
bool IATouchDelegate_isTouchEventNotEmpty(IATouchDelegate *);
void IATouchDelegate_resetCurrentTouchEvent(IATouchDelegate *);

void IATouchDelegate_touchBegan(IATouchDelegate *);
void IATouchDelegate_touchMoved(IATouchDelegate *);
void IATouchDelegate_touchEnded(IATouchDelegate *);
void IATouchDelegate_touchCanceled(IATouchDelegate *);

void IATouchDelegate_deinit(IATouchDelegate *);

#include "IATouchDelegate+Generated.h"

#endif
