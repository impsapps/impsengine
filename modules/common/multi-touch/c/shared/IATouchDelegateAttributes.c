#include "IALibrary.h"
#include "IATouchDelegateAttributes.h"

#define CLASSNAME "IATouchDelegateAttributes"


bool IATouchDelegateAttributes_returnTrue(void * object, IATouch touch);
bool IATouchDelegateAttributes_returnFalse(void * object, IATouch touch);

void IATouchDelegateAttributes_make(IATouchDelegateAttributes * this, void * correspondingObject){
    *this = (IATouchDelegateAttributes){
		.correspondingObject = correspondingObject,
        .wantToUseTouch = IATouchDelegateAttributes_returnFalse,
        .wantToConsumeTouch = IATouchDelegateAttributes_returnFalse
    };
}

void IATouchDelegateAttributes_setAlwaysWantToConsumeTouch(IATouchDelegateAttributes * this, bool alwaysWantToConsumeTouch){
    if (alwaysWantToConsumeTouch) {
        this->wantToConsumeTouch = IATouchDelegateAttributes_returnTrue;
    }else{
        this->wantToConsumeTouch = IATouchDelegateAttributes_returnFalse;
    }
}

bool IATouchDelegateAttributes_returnTrue(void * object, IATouch touch){
    return true;
}

bool IATouchDelegateAttributes_returnFalse(void * object, IATouch touch){
    return false;
}

