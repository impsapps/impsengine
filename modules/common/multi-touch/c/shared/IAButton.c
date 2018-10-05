#include "IATouchManager.h"
#include "IALibrary.h"
#include "IAButton.h"
#include "IAArrayListIterator.h"

#define CLASSNAME "IAButton"

void IAButton_setRectFunction(IAButton * this, IARect rect);

bool IAButton_wantToUseTouch(IAButton * this, IATouch touch);
IARect IAButton_addRectExtensionTouchBeganToRect(IAButton * this, IARect rect);
IARect IAButton_addRectExtensionTouchMovedOutsideToRect(IAButton * this, IARect rect);

void IAButton_onTouchBegan(IAButton * this, size_t numTouches, IATouch touches[numTouches]);
void IAButton_onTouchMoved(IAButton * this, size_t numTouches, IATouch touches[numTouches]);
void IAButton_onTouchEnded(IAButton * this, size_t numTouches, IATouch touches[numTouches]);
void IAButton_onTouchCanceled(IAButton * this);

void IAButton_exeOnClick(IAButton * this);
void IAButton_exeOnIsTouchedChanged(IAButton * this, bool isTouched);

void IAButton_drawFunction(const IAButton * this);


void IAButton_init(IAButton * this, const IAButtonAttributes * attributes){
    IADrawableRect_make(&this->drawableRect, (void (*)(const IADrawable *)) IAButton_drawFunction, (void (*)(IADrawableRect *, IARect)) IAButton_setRectFunction, NULL);
    IADrawableRect * normal = IAButtonAttributes_getNormal(attributes);
    if (normal != NULL){
        IADrawableRect_retain(normal);
    }
    this->normal = normal;

    IADrawableRect * touched = IAButtonAttributes_getTouched(attributes);
    if (touched != NULL){
        IADrawableRect_retain(touched);
    }
    this->touched = touched;
    
    IATouchDelegateAttributes attr;
    IATouchDelegateAttributes_make(&attr, this);
    IATouchDelegateAttributes_setWantToUseTouchFunction(&attr, (bool (*)(void *, IATouch)) IAButton_wantToUseTouch);
    IATouchDelegateAttributes_setAlwaysWantToConsumeTouch(&attr, true);
    IATouchDelegateAttributes_setOnTouchBeganFunction(&attr, (void(*)(void *, size_t, IATouch touches[])) IAButton_onTouchBegan);
    IATouchDelegateAttributes_setOnTouchMovedFunction(&attr, (void(*)(void *, size_t, IATouch touches[])) IAButton_onTouchMoved);
    IATouchDelegateAttributes_setOnTouchEndedFunction(&attr, (void(*)(void *, size_t, IATouch touches[])) IAButton_onTouchEnded);
    IATouchDelegateAttributes_setOnTouchCanceledFunction(&attr, (void(*)(void *)) IAButton_onTouchCanceled);
    IATouchDelegateAttributes_setZOrder(&attr, IAButtonAttributes_getZOrder(attributes));
    IATouchDelegate_init(&this->touchDelegate, &attr);

    IA_STRUCT_ARRAY_LIST_MALLOC_MAKE(this->validTouches, IATouch, 10);
    
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
    IA_incrementInitCount();
}

bool IAButton_wantToUseTouch(IAButton * this, IATouch touch){
    IARect rect = IAButton_addRectExtensionTouchBeganToRect(this, IAButton_getRect(this));
    return IARect_isPointWithin(rect, touch.location);
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

void IAButton_onTouchBegan(IAButton * this, size_t numTouches, IATouch touches[numTouches]){
    bool originalIsTouched = IAButton_isTouched(this);
    for (size_t i = 0; i < numTouches; i++) {
        IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_IF_NEEDED(this->validTouches, IATouch);
        IAStructArrayList_IATouch_add(this->validTouches, touches[i]);
    }
    bool newIsTouched = IAButton_isTouched(this);
    if(newIsTouched != originalIsTouched){
        IAButton_exeOnIsTouchedChanged(this, newIsTouched);
    }
}

void IAButton_onTouchMoved(IAButton * this, size_t numTouches, IATouch touches[numTouches]){
    bool originalIsTouched = IAButton_isTouched(this);
    IARect rectForMovingOutside = IAButton_addRectExtensionTouchBeganToRect(this, IAButton_getRect(this));
    rectForMovingOutside = IAButton_addRectExtensionTouchMovedOutsideToRect(this, rectForMovingOutside);

    for (size_t iTouch = 0; iTouch < numTouches; iTouch++) {
        IATouch touch = touches[iTouch];
        for (size_t iValidTouch = 0; iValidTouch < IAStructArrayList_IATouch_getCurrentSize(this->validTouches); iValidTouch++){
            IATouch validTouch = IAStructArrayList_IATouch_get(this->validTouches, iValidTouch);
            if (IATouch_hasSameIdentifier(touch, validTouch) && IARect_isPointWithin(rectForMovingOutside, touch.location) == false) {
                IAStructArrayList_IATouch_removeAtIndex(this->validTouches, iValidTouch);
                break;
            }
        }
    }
    bool newIsTouched = IAButton_isTouched(this);
    if(newIsTouched != originalIsTouched){
        IAButton_exeOnIsTouchedChanged(this, newIsTouched);
    }
}

void IAButton_onTouchEnded(IAButton * this, size_t numTouches, IATouch touches[numTouches]){
    bool originalIsTouched = IAButton_isTouched(this);
    bool anyTouchIsValid = false;
    for (size_t iTouch = 0; iTouch < numTouches; iTouch++) {
        IATouch touch = touches[iTouch];
        for (size_t iValidTouch = 0; iValidTouch < IAStructArrayList_IATouch_getCurrentSize(this->validTouches); iValidTouch++){
            IATouch validTouch = IAStructArrayList_IATouch_get(this->validTouches, iValidTouch);
            if (IATouch_hasSameIdentifier(touch, validTouch)) {
                IAStructArrayList_IATouch_removeAtIndex(this->validTouches, iValidTouch);
                anyTouchIsValid = true;
                break;
            }
        }
    }
    bool newIsTouched = IAButton_isTouched(this);
    if(newIsTouched != originalIsTouched){
        IAButton_exeOnIsTouchedChanged(this, newIsTouched);
    }
    if (IAStructArrayList_IATouch_isEmpty(this->validTouches)) {
        if (anyTouchIsValid) {
            IAButton_exeOnClick(this);
        }
    }
}

void IAButton_onTouchCanceled(IAButton * this){
    IAStructArrayList_IATouch_clear(this->validTouches);
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
            IAStructArrayList_IATouch_clear(this->validTouches);
        }
    }
    
}

bool IAButton_isTouched(const IAButton * this){
    if (IAStructArrayList_IATouch_isEmpty(this->validTouches) == true) {
        return false;
    }else{
        return true;
    }
}

void IAButton_setRectFunction(IAButton * this, IARect rect){
    if (this->normal != NULL) {
        IADrawableRect_setRect(this->normal, rect);
    }if (this->touched != NULL) {
        IADrawableRect_setRect(this->touched, rect);
    }
}

void IAButton_drawFunction(const IAButton * this){
    if (IAButton_isTouched(this) == false) {
        if (this->normal != NULL) {
            IAButton_drawButtonNormal(this);
        }
    }else{
        if (this->touched != NULL) {
            IAButton_drawButtonTouched(this);
        }else if (this->normal != NULL){
            IAButton_drawButtonNormal(this);
        }
    }
}


void IAButton_drawButtonNormal(const IAButton * this){
    assert(this->normal != NULL);
    IADrawableRect_draw(this->normal);
}

void IAButton_drawButtonTouched(const IAButton * this){
    assert(this->touched != NULL);
    IADrawableRect_draw(this->touched);
}

void IAButton_deinit(IAButton * this){
    if (this->normal != NULL){
        IADrawableRect_release(this->normal);
    }
    if (this->touched != NULL){
        IADrawableRect_release(this->touched);
    }
    if (this->isClickable) {
        IATouchManager_unregisterTouchDelegate(&this->touchDelegate);
    }
    IATouchDelegate_deinit(&this->touchDelegate);
    IA_STRUCT_ARRAY_LIST_FREE(this->validTouches);
    IA_decrementInitCount();
}


