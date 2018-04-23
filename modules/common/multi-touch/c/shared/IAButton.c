//
//  IAButton.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 24.05.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IATouchManager.h"
#include "IALibrary.h"
#include "IAButton.h"
#include "IAArrayListIterator.h"

#define CLASSNAME "IAButton"

void IAButton_setRectFunction(IAButton * this, IARect rect);

void IAButton_updateRect(IAButton * this);
void IAButton_updateRectOfImage(IAButton * this, IAImage * image);
bool IAButton_wantToUseTouch(IAButton * this, IATouch * touch);
IARect IAButton_addRectExtensionTouchBeganToRect(IAButton * this, IARect rect);
IARect IAButton_addRectExtensionTouchMovedOutsideToRect(IAButton * this, IARect rect);

void IAButton_onTouchBegan(IAButton * this, IAArrayList * list);
void IAButton_onTouchMoved(IAButton * this, IAArrayList * list);
void IAButton_onTouchEnded(IAButton * this, IAArrayList * list);

void IAButton_exeOnClick(IAButton * this);
void IAButton_exeOnIsTouchedChanged(IAButton * this, bool isTouched);

void IAButton_drawFunction(const IAButton * this);


void IAButton_init(IAButton * this, const IAButtonAttributes * attributes){
    IADrawableRect_make((IADrawableRect *) this, (void (*)(const IADrawable *)) IAButton_drawFunction, (void (*)(IADrawableRect *, IARect)) IAButton_setRectFunction);
    IAImage * image = IAButtonAttributes_getButtonImageNormal(attributes);
    if (image != NULL){
        this->buttonImageNormal = IAImage_newCopy(image);
    }else{
        this->buttonImageNormal = NULL;
    }

    image = IAButtonAttributes_getButtonImageTouched(attributes);
    if (image != NULL){
        this->buttonImageTouched = IAImage_newCopy(image);
    }else{
        this->buttonImageTouched = NULL;
    }
    
    IATouchDelegateAttributes attr;
    IATouchDelegateAttributes_make(&attr, this);
    IATouchDelegateAttributes_setWantToUseTouchFunction(&attr, (bool (*)(void *, IATouch *)) IAButton_wantToUseTouch);
    IATouchDelegateAttributes_setAlwaysWantToConsumeTouch(&attr, true);
    IATouchDelegateAttributes_setOnTouchBeganFunction(&attr, (void(*)(void *, IAArrayList *)) IAButton_onTouchBegan);
    IATouchDelegateAttributes_setOnTouchMovedFunction(&attr, (void(*)(void *, IAArrayList *)) IAButton_onTouchMoved);
    IATouchDelegateAttributes_setOnTouchEndedFunction(&attr, (void(*)(void *, IAArrayList *)) IAButton_onTouchEnded);
    IATouchDelegateAttributes_setZOrder(&attr, IAButtonAttributes_getZOrder(attributes));
    IATouchDelegate_init(&this->touchDelegate, &attr);
    
    IAArrayList_init(&this->validTouchIds, 10);
    this->touchCount = 0;
    
    this->rectExtensionForTouchBeganLeft = IAButtonAttributes_getRectExtensionForTouchBeganLeft(attributes);
    this->rectExtensionForTouchBeganTop = IAButtonAttributes_getRectExtensionForTouchBeganTop(attributes);
    this->rectExtensionForTouchBeganRight = IAButtonAttributes_getRectExtensionForTouchBeganRight(attributes);
    this->rectExtensionForTouchBeganBottom = IAButtonAttributes_getRectExtensionForTouchBeganBottom(attributes);
    
    this->rectExtensionForTouchMovedOutsideLeft = IAButtonAttributes_getRectExtensionForTouchMovedOutsideLeft(attributes);
    this->rectExtensionForTouchMovedOutsideTop = IAButtonAttributes_getRectExtensionForTouchMovedOutsideTop(attributes);
    this->rectExtensionForTouchMovedOutsideRight = IAButtonAttributes_getRectExtensionForTouchMovedOutsideRight(attributes);
    this->rectExtensionForTouchMovedOutsideBottom = IAButtonAttributes_getRectExtensionForTouchMovedOutsideBottom(attributes);
    
    this->isClickable = false;
    
    this->correspondingObject = IAButtonAttributes_getCorrespondingObject(attributes);
    
    this->onClick = IAButtonAttributes_getOnClickFunction(attributes);
    this->onIsTouchedChanged = IAButtonAttributes_getOnIsTouchedChangedFunction(attributes);
    
    this->tag = IAButtonAttributes_getTag(attributes);
    
    IAButton_setRect(this, IAButtonAttributes_getRect(attributes));
    IA_increaseAllocationCount();
}

bool IAButton_wantToUseTouch(IAButton * this, IATouch * touch){
    IARect rect = IAButton_addRectExtensionTouchBeganToRect(this, IAButton_getRect(this));
    return IATouch_isInRect(touch, rect);
}

IARect IAButton_addRectExtensionTouchBeganToRect(IAButton * this, IARect rect){
    float width = rect.size.width + this->rectExtensionForTouchBeganLeft + this->rectExtensionForTouchBeganRight;
    float height = rect.size.height + this->rectExtensionForTouchBeganTop + this->rectExtensionForTouchBeganBottom;
    return IARect_make(rect.origin.x - this->rectExtensionForTouchBeganLeft, rect.origin.y - this->rectExtensionForTouchBeganTop, width, height);
}

IARect IAButton_addRectExtensionTouchMovedOutsideToRect(IAButton * this, IARect rect){
    float width = rect.size.width + this->rectExtensionForTouchMovedOutsideLeft + this->rectExtensionForTouchMovedOutsideRight;
    float height = rect.size.height + this->rectExtensionForTouchMovedOutsideTop + this->rectExtensionForTouchMovedOutsideBottom;
    return IARect_make(rect.origin.x - this->rectExtensionForTouchMovedOutsideLeft, rect.origin.y - this->rectExtensionForTouchMovedOutsideTop, width, height);
}

void IAButton_onTouchBegan(IAButton * this, IAArrayList * list){
    bool originalIsTouched = IAButton_isTouched(this);
    IATouch * touch;
    foreach (touch in arrayList(list)) {
        IAArrayList_add(&this->validTouchIds, touch);
        this->touchCount ++;
    }
    bool newIsTouched = IAButton_isTouched(this);
    if(newIsTouched != originalIsTouched){
        IAButton_exeOnIsTouchedChanged(this, newIsTouched);
    }
}

void IAButton_onTouchMoved(IAButton * this, IAArrayList * list){
    bool originalIsTouched = IAButton_isTouched(this);
    IARect rectForMovingOutside = IAButton_addRectExtensionTouchBeganToRect(this, IAButton_getRect(this));
    rectForMovingOutside = IAButton_addRectExtensionTouchMovedOutsideToRect(this, rectForMovingOutside);
    
    IATouch * touch;
    foreach (touch in arrayList(list)) {
        IATouch * validTouch;
        size_t index = 0;
        foreach (validTouch in arrayList(&this->validTouchIds)){
            if (validTouch == touch && IATouch_isInRect(touch, rectForMovingOutside) == false) {
                IAArrayList_removeAtIndex(&this->validTouchIds, index);
                break;
            }
            index++;
        }
    }
    bool newIsTouched = IAButton_isTouched(this);
    if(newIsTouched != originalIsTouched){
        IAButton_exeOnIsTouchedChanged(this, newIsTouched);
    }
}

void IAButton_onTouchEnded(IAButton * this, IAArrayList * list){
    bool originalIsTouched = IAButton_isTouched(this);
    bool anyTouchIsValid = false;
    IATouch * touch;
    foreach (touch in arrayList(list)) {
        IATouch * validTouch;
        size_t index = 0;
        foreach (validTouch in arrayList(&this->validTouchIds)){
            if (touch == validTouch) {
                IAArrayList_removeAtIndex(&this->validTouchIds, index);
                anyTouchIsValid = true;
                break;
            }
            index++;
        }
        this->touchCount--;
    }
    bool newIsTouched = IAButton_isTouched(this);
    if(newIsTouched != originalIsTouched){
        IAButton_exeOnIsTouchedChanged(this, newIsTouched);
    }
    if (this->touchCount == 0) {
        if (anyTouchIsValid) {
            IAButton_exeOnClick(this);
        }
    }
}

void IAButton_exeOnClick(IAButton * this){
    if (this->onClick != NULL) {
        this->onClick(this->correspondingObject, this);
    }
}

void IAButton_exeOnIsTouchedChanged(IAButton * this, bool isTouched){
    debugAssert(IAButton_isTouched(this) == isTouched);
    if (this->onIsTouchedChanged != NULL) {
        this->onIsTouchedChanged(this->correspondingObject, this, isTouched);
    }
}

void IAButton_setIsClickable(IAButton * this, bool isClickable){
    if (this->isClickable != isClickable) {
        this->isClickable = isClickable;
        if (this->isClickable) {
            IATouchManager_registerTouchDelegate(&this->touchDelegate);
        }else{
            IATouchManager_unregisterTouchDelegate(&this->touchDelegate);
            IAArrayList_clear(&this->validTouchIds);
            this->touchCount = 0;
        }
    }
    
}

bool IAButton_isTouched(const IAButton * this){
    if (IAArrayList_isEmpty(&this->validTouchIds) == true) {
        return false;
    }else{
        return true;
    }
}

void IAButton_setRectFunction(IAButton * this, IARect rect){
    IAButton_updateRect(this);
}

void IAButton_updateRect(IAButton * this){
    IAButton_updateRectOfImage(this, this->buttonImageNormal);
    IAButton_updateRectOfImage(this, this->buttonImageTouched);
}

void IAButton_updateRectOfImage(IAButton * this, IAImage * image){
    if (image != NULL) {
        IAImage_setRect(image, IAButton_getRect(this));
    }
}

void IAButton_drawFunction(const IAButton * this){
    if (IAButton_isTouched(this) == false) {
        if (this->buttonImageNormal != NULL) {
            IAButton_drawButtonNormal(this);
        }
    }else{
        if (this->buttonImageTouched != NULL) {
            IAButton_drawButtonTouched(this);
        }else if (this->buttonImageNormal != NULL){
            IAButton_drawButtonNormal(this);
        }
    }
}


void IAButton_drawButtonNormal(const IAButton * this){
    assert(this->buttonImageNormal != NULL);
    IAImage_draw(this->buttonImageNormal);
}

void IAButton_drawButtonTouched(const IAButton * this){
    assert(this->buttonImageTouched != NULL);
    IAImage_draw(this->buttonImageTouched);
}

void IAButton_deinit(IAButton * this){
    if (this->buttonImageNormal != NULL){
        IAImage_release(this->buttonImageNormal);
    }
    if (this->buttonImageTouched != NULL){
        IAImage_release(this->buttonImageTouched);
    }
    if (this->isClickable) {
        IATouchManager_unregisterTouchDelegate(&this->touchDelegate);
    }
    IATouchDelegate_deinit(&this->touchDelegate);
    IAArrayList_deinit(&this->validTouchIds);
    IA_decreaseAllocationCount();
}


