//
//  IATouchHandler.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 28.05.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IATouchHandler.h"
#include "IATouch+Internal.h"
#include "IAArrayListIterator.h"

#define CLASSNAME "IATouchHandler"


void IATouchHandler_init(IATouchHandler * this, long touchId, IAPoint location){
    this->touchId = touchId;
    IATouch_make(&this->touch, location);
    IAArrayList_init(&this->touchDelegates, 5);
    IA_increaseAllocationCount();
}

void IATouchHandler_reinit(IATouchHandler * this, long touchId, IAPoint location){
    this->touchId = touchId;
    IATouch_make(&this->touch, location);
    IAArrayList_clear(&this->touchDelegates);
}

void IATouchHandler_setTouchLocation(IATouchHandler * this, IAPoint newLocation){
    IATouch_setLocation(&this->touch, newLocation);
}

void IATouchHandler_registerTouchDelegate(IATouchHandler * this, IATouchDelegate * touchDelegate){
    IAArrayList_add(&this->touchDelegates, touchDelegate);
}

void IATouchHandler_prepareTouchDelegates(IATouchHandler * this){
    IATouchDelegate * delegate;
    foreach (delegate in arrayList(&this->touchDelegates)) {
        IATouchDelegate_addTouchToTouchEvent(delegate, &this->touch);
    }
}

void IATouchHandler_unregisterTouchDelegate(IATouchHandler * this, IATouchDelegate * touchDelegate){
    IAArrayList_removeObject(&this->touchDelegates, touchDelegate);
}

void IATouchHandler_deinit(IATouchHandler * this){
    IAArrayList_deinit(&this->touchDelegates);
    IA_decreaseAllocationCount();
}


