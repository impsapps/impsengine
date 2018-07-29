//
//  IATouchDelegate.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 28.05.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IATouchDelegate.h"

#define CLASSNAME "IATouchDelegate"


void IATouchDelegate_init(IATouchDelegate * this, const IATouchDelegateAttributes * attr){
    *this = (IATouchDelegate){
        .correspondingObject = IATouchDelegateAttributes_getCorrespondingObject(attr),
        .wantToUseTouch = IATouchDelegateAttributes_getWantToUseTouchFunction(attr),
        .wantToConsumeTouch = IATouchDelegateAttributes_getWantToConsumeTouchFunction(attr),
        .touchBegan = IATouchDelegateAttributes_getOnTouchBeganFunction(attr),
        .touchMoved = IATouchDelegateAttributes_getOnTouchMovedFunction(attr),
        .touchEnded = IATouchDelegateAttributes_getOnTouchEndedFunction(attr),
        .touchCanceled = IATouchDelegateAttributes_getOnTouchCanceledFunction(attr),
        .zOrder = IATouchDelegateAttributes_getZOrder(attr)
    };
    IAArrayList_init(&this->touchesForTouchEvent, 10);
    IA_incrementInitCount();
}

void IATouchDelegate_addTouchToTouchEvent(IATouchDelegate * this, IATouch * touch){
    IAArrayList_add(&this->touchesForTouchEvent, touch);
}

bool IATouchDelegate_isTouchEventNotEmpty(IATouchDelegate * this){
    if (IAArrayList_isEmpty(&this->touchesForTouchEvent) == true) {
        return false;
    }else{
        return true;
    }
}

void IATouchDelegate_resetCurrentTouchEvent(IATouchDelegate * this){
    IAArrayList_clear(&this->touchesForTouchEvent);
}

void IATouchDelegate_touchBegan(IATouchDelegate * this){
    if (this->touchBegan != NULL) {
        this->touchBegan(this->correspondingObject, &this->touchesForTouchEvent);
    }
}

void IATouchDelegate_touchMoved(IATouchDelegate * this){
    if (this->touchMoved != NULL) {
        this->touchMoved(this->correspondingObject, &this->touchesForTouchEvent);
    }
}

void IATouchDelegate_touchEnded(IATouchDelegate * this){
    if (this->touchEnded != NULL) {
        this->touchEnded(this->correspondingObject, &this->touchesForTouchEvent);
    }
}

void IATouchDelegate_touchCanceled(IATouchDelegate * this){
    if (this->touchCanceled != NULL) {
        this->touchCanceled(this->correspondingObject);
    }
}

void IATouchDelegate_deinit(IATouchDelegate * this){
    IAArrayList_deinit(&this->touchesForTouchEvent);
    IA_decrementInitCount();
}


