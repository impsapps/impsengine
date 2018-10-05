#include "IALibrary.h"
#include "IATextureDelegateAttributes.h"

#define CLASSNAME "IATextureDelegateAttributes"


void IATextureDelegateAttributes_make(IATextureDelegateAttributes * this, void * correspondingObject){
    *this = (IATextureDelegateAttributes){
        .correspondingObject = correspondingObject
    };
}


