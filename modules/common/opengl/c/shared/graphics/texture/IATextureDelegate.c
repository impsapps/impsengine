#include "IALibrary.h"
#include "IATextureDelegate.h"

#define CLASSNAME "IATextureDelegate"


void IATextureDelegate_make(IATextureDelegate * this, IATextureDelegateAttributes * attributes){
    *this = (IATextureDelegate){
        .correspondingObject = IATextureDelegateAttributes_getCorrespondingObject(attributes),
        .onBitmapUsageBegin = IATextureDelegateAttributes_getOnBitmapUsageBeginFunction(attributes),
        .onBitmapUsageEnd = IATextureDelegateAttributes_getOnBitmapUsageEndFunction(attributes)
    };
}


