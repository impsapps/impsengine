#include "IALibrary.h"
#include "IAButtonAttributes.h"
#include "IAViewPort.h"

#define CLASSNAME "IAButtonAttributes"


void IAButtonAttributes_make(IAButtonAttributes * this){
    *this = (IAButtonAttributes){
    };
}

void IAButtonAttributes_setRectExtensionForTouchBegan(IAButtonAttributes * this, float extension){
    this->rectExtensionForTouchBeganLeft = extension;
    this->rectExtensionForTouchBeganTop = extension;
    this->rectExtensionForTouchBeganRight = extension;
    this->rectExtensionForTouchBeganBottom = extension;
}

void IAButtonAttributes_setRectExtensionForTouchMovedOutside(IAButtonAttributes * this, float extension){
    this->rectExtensionForTouchMovedOutsideLeft = extension;
    this->rectExtensionForTouchMovedOutsideTop = extension;
    this->rectExtensionForTouchMovedOutsideRight = extension;
    this->rectExtensionForTouchMovedOutsideBottom = extension;
}

