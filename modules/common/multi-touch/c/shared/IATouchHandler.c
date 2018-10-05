#include "IALibrary.h"
#include "IATouchHandler.h"
#include "IAArrayListIterator.h"

#define CLASSNAME "IATouchHandler"


void IATouchHandler_init(IATouchHandler * this, long touchId, IAPoint location){
    this->base = IAObject_make(this);
    this->touch = IATouch_make(touchId, location);
    IAArrayList_init(&this->touchDelegates, 5);
    IA_incrementInitCount();
}

void IATouchHandler_reinit(IATouchHandler * this, long touchId, IAPoint location){
    this->touch = IATouch_make(touchId, location);
    IAArrayList_clear(&this->touchDelegates);
}

void IATouchHandler_setTouchLocation(IATouchHandler * this, IAPoint newLocation){
    this->touch.location = newLocation;
}

void IATouchHandler_registerTouchDelegate(IATouchHandler * this, IATouchDelegate * touchDelegate){
    IAArrayList_add(&this->touchDelegates, touchDelegate);
}

void IATouchHandler_prepareTouchDelegates(IATouchHandler * this){
    IATouchDelegate * delegate;
    foreach (delegate in arrayList(&this->touchDelegates)) {
        IATouchDelegate_addTouchToTouchEvent(delegate, this->touch);
    }
}

void IATouchHandler_unregisterTouchDelegate(IATouchHandler * this, IATouchDelegate * touchDelegate){
    IAArrayList_removeObject(&this->touchDelegates, touchDelegate);
}

void IATouchHandler_deinit(IATouchHandler * this){
    IAArrayList_deinit(&this->touchDelegates);
    IA_decrementInitCount();
}


