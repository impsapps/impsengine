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
#include "IAStructArrayList.h"
#include <stdbool.h>

#ifndef IAStructArrayList_IATouch_h
#define IAStructArrayList_IATouch_h
IA_STRUCT_ARRAY_LIST(IATouch);
#endif

typedef struct{
    void * correspondingObject;
    //@exe
    bool (*wantToUseTouch)(void * correspondingObject, IATouch touch);
    //@exe
    bool (*wantToConsumeTouch)(void * correspondingObject, IATouch touch);
    
    void (*touchBegan)(void * correspondingObject, size_t numTouches, IATouch touches[numTouches]);
    void (*touchMoved)(void * correspondingObject, size_t numTouches, IATouch touches[numTouches]);
    void (*touchEnded)(void * correspondingObject, size_t numTouches, IATouch touches[numTouches]);
    void (*touchCanceled)(void * correspondingObject);

    IAStructArrayList_IATouch * touches;

    //@get
    int zOrder;
} IATouchDelegate;


void IATouchDelegate_init(IATouchDelegate *, const IATouchDelegateAttributes * attr);

void IATouchDelegate_addTouchToTouchEvent(IATouchDelegate *, IATouch touch);
bool IATouchDelegate_isTouchEventNotEmpty(IATouchDelegate *);
void IATouchDelegate_resetCurrentTouchEvent(IATouchDelegate *);

void IATouchDelegate_touchBegan(IATouchDelegate *);
void IATouchDelegate_touchMoved(IATouchDelegate *);
void IATouchDelegate_touchEnded(IATouchDelegate *);
void IATouchDelegate_touchCanceled(IATouchDelegate *);

void IATouchDelegate_deinit(IATouchDelegate *);

#include "IATouchDelegate+Generated.h"

#endif
