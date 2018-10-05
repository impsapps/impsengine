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
    IA_STRUCT_ARRAY_LIST_MALLOC_MAKE(this->touches, IATouch, 10);
    IA_incrementInitCount();
}

void IATouchDelegate_addTouchToTouchEvent(IATouchDelegate * this, IATouch touch){
    IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_IF_NEEDED(this->touches, IATouch);
    IAStructArrayList_IATouch_add(this->touches, touch);
}

bool IATouchDelegate_isTouchEventNotEmpty(IATouchDelegate * this){
    if (IAStructArrayList_IATouch_isEmpty(this->touches) == true) {
        return false;
    }else{
        return true;
    }
}

void IATouchDelegate_resetCurrentTouchEvent(IATouchDelegate * this){
    IAStructArrayList_IATouch_clear(this->touches);
}

void IATouchDelegate_touchBegan(IATouchDelegate * this){
    if (this->touchBegan != NULL) {
        this->touchBegan(this->correspondingObject, this->touches->currentSize, this->touches->buffer);
    }
}

void IATouchDelegate_touchMoved(IATouchDelegate * this){
    if (this->touchMoved != NULL) {
        this->touchMoved(this->correspondingObject, this->touches->currentSize, this->touches->buffer);
    }
}

void IATouchDelegate_touchEnded(IATouchDelegate * this){
    if (this->touchEnded != NULL) {
        this->touchEnded(this->correspondingObject, this->touches->currentSize, this->touches->buffer);
    }
}

void IATouchDelegate_touchCanceled(IATouchDelegate * this){
    if (this->touchCanceled != NULL) {
        this->touchCanceled(this->correspondingObject);
    }
}

void IATouchDelegate_deinit(IATouchDelegate * this){
    IA_STRUCT_ARRAY_LIST_FREE(this->touches);
    IA_decrementInitCount();
}


