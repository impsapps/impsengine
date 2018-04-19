//
//  IATextureDelegate.c
//  OpenGL
//
//  Created by Konstantin Merker on 01/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

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


