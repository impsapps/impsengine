//
//  IATouchManager.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 28.05.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IATouchManager.h"
#include "IAArrayListIterator.h"

#define CLASSNAME "IATouchManager"


void IATouchManager_resetCurrentTouchEvents();
void IATouchManager_prepareNewTouchEvent(size_t lengthOfTouchHandlers, IATouchHandler * touchHandlers[lengthOfTouchHandlers]);

void IATouchManager_executeTouchEventWithTouches(void (*executeMethod)(IATouchDelegate * touchHandler), size_t lengthOfTouchHandlers, IATouchHandler * touchHandlers[lengthOfTouchHandlers]);
void IATouchManager_executeTouchEvent(void (*executeMethod)(IATouchDelegate * touchHandler));


static IAArrayList * registeredTouchDelegates;
static IAArrayList * touchHandlers;
static IAArrayList * unusedTouchHandlers;

void IATouchManager_commence(){
    registeredTouchDelegates = IAArrayList_new(10);
    touchHandlers = IAArrayList_new(10);
    unusedTouchHandlers = IAArrayList_new(10);
}

void IATouchManager_registerTouchDelegate(IATouchDelegate * touchDelegate){
    size_t index = 0;
    int zOrder = IATouchDelegate_getZOrder(touchDelegate);
    IATouchDelegate * registeredTouchDelegate;
    foreach (registeredTouchDelegate in arrayList(registeredTouchDelegates)){
        if (zOrder >= IATouchDelegate_getZOrder(registeredTouchDelegate)) {
            break;
        }
        index++;
    }
    IAArrayList_insertAtIndex(registeredTouchDelegates, index, touchDelegate);
}

void IATouchManager_unregisterTouchDelegate(IATouchDelegate * touchDelegate){
    IAArrayList_removeObject(registeredTouchDelegates, touchDelegate);
    IATouchHandler * touchHandler;
    foreach (touchHandler in arrayList(touchHandlers)) {
        IATouchHandler_unregisterTouchDelegate(touchHandler, touchDelegate);
    }
}

IATouchHandler * IATouchManager_createNewTouchHandler(long touchId, IAPoint location){
    IATouchHandler * handler;
    if (IAArrayList_isEmpty(unusedTouchHandlers)) {
        handler = IATouchHandler_new(touchId, location);
    }else{
        handler = IAArrayList_removeAtIndex(unusedTouchHandlers, 0);
        IATouchHandler_reinit(handler, touchId, location);
    }
    
    IAArrayList_add(touchHandlers, handler);
    IATouch * touch = IATouchHandler_getTouch(handler);
    IATouchDelegate * touchDelegate;
    foreach (touchDelegate in arrayList(registeredTouchDelegates)) {
        if(IATouchDelegate_wantToUseTouch(touchDelegate, touch) == true){
            IATouchHandler_registerTouchDelegate(handler, touchDelegate);
            if(IATouchDelegate_wantToConsumeTouch(touchDelegate, touch)){
                break;
            }
        }
    }
    return handler;
}

IATouchHandler * IATouchManager_getTouchHandler(long touchId){
    IATouchHandler * handler = NULL;
    foreach (handler in arrayList(touchHandlers)){
        if (IATouchHandler_getTouchId(handler) == touchId) {
            break;
        }
    }
    return handler;
}

void IATouchManager_destroyTouchHandler(IATouchHandler * touchHandler){
    IAArrayList_removeObject(touchHandlers, touchHandler);
    IAArrayList_add(unusedTouchHandlers, touchHandler);
}

void IATouchManager_onTouchBegan(size_t lengthOfTouchHandlers, IATouchHandler * touchHandlers[lengthOfTouchHandlers]){
    IATouchManager_executeTouchEventWithTouches(IATouchDelegate_touchBegan, lengthOfTouchHandlers, touchHandlers);
}

void IATouchManager_onTouchMoved(size_t lengthOfTouchHandlers, IATouchHandler * touchHandlers[lengthOfTouchHandlers]){
    IATouchManager_executeTouchEventWithTouches(IATouchDelegate_touchMoved, lengthOfTouchHandlers, touchHandlers);
}

void IATouchManager_onTouchEnded(size_t lengthOfTouchHandlers, IATouchHandler * touchHandlers[lengthOfTouchHandlers]){
    IATouchManager_executeTouchEventWithTouches(IATouchDelegate_touchEnded, lengthOfTouchHandlers, touchHandlers);
}

void IATouchManager_onTouchCanceled(){
    IATouchManager_resetCurrentTouchEvents();
    IATouchManager_executeTouchEvent(IATouchDelegate_touchCanceled);
}

void IATouchManager_executeTouchEventWithTouches(void (*executeMethod)(IATouchDelegate * touchHandler), size_t lengthOfTouchHandlers, IATouchHandler * touchHandlers[lengthOfTouchHandlers]){
    IATouchManager_resetCurrentTouchEvents();
    IATouchManager_prepareNewTouchEvent(lengthOfTouchHandlers, touchHandlers);
    IATouchManager_executeTouchEvent(executeMethod);
}

void IATouchManager_resetCurrentTouchEvents(){
    IAArrayList_callFunctionOnAllObjects(registeredTouchDelegates, (void (*)(void *)) IATouchDelegate_resetCurrentTouchEvent);
}

void IATouchManager_prepareNewTouchEvent(size_t lengthOfTouchHandlers, IATouchHandler * touchHandlers[lengthOfTouchHandlers]){
    for (size_t i = 0; i < lengthOfTouchHandlers; i++) {
        IATouchHandler_prepareTouchDelegates(touchHandlers[i]);
    }
}

static IAArrayList * touchesToExcecuteTemp = NULL;
void IATouchManager_executeTouchEvent(void (*executeMethod)(IATouchDelegate * touchHandler)){
    if (touchesToExcecuteTemp == NULL) {
        touchesToExcecuteTemp = IAArrayList_new(10);
    }else{
        IAArrayList_clear(touchesToExcecuteTemp);
    }
    
    IATouchDelegate * delegate;
    foreach (delegate in arrayList(registeredTouchDelegates)) {
        if (IATouchDelegate_isTouchEventNotEmpty(delegate)) {
            IAArrayList_add(touchesToExcecuteTemp, delegate);
        }
    }
    IAArrayList_callFunctionOnAllObjects(touchesToExcecuteTemp, (void (*)(void *)) executeMethod);
}

void IATouchManager_terminate(){
    IAArrayList_release(registeredTouchDelegates);
    IAArrayList_callFunctionOnAllObjects(touchHandlers, (void (*)(void *)) IATouchHandler_release);
    IAArrayList_release(touchHandlers);
    IAArrayList_callFunctionOnAllObjects(unusedTouchHandlers, (void (*)(void *)) IATouchHandler_release);
    IAArrayList_release(unusedTouchHandlers);
    if (touchesToExcecuteTemp != NULL) {
        IAArrayList_release(touchesToExcecuteTemp);
    }
}


