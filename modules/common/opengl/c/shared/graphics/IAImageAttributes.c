//
//  IAImageAttributes.c
//  OpenGL
//
//  Created by Konstantin Merker on 26/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAImageAttributes.h"
#include "IAViewPort.h"

#define CLASSNAME "IAImageAttributes"


void IAImageAttributes_make(IAImageAttributes * this, IATexture * texture, IATextureSelection textureSelection){
    *this = (IAImageAttributes){
        .texture = texture,
        .textureSelection = textureSelection
    };
}

void IAImageAttributes_setTextureSelection(IAImageAttributes * this, IATextureSelection textureSelection){
    this->textureSelection = textureSelection;
}

void IAImageAttributes_setTrimmedRect(IAImageAttributes * this, IARect trimmedRect, IASize originalSizeOfImage){
    this->trimmedRect = trimmedRect;
    this->originalSizeOfImageForTrimmedRect = originalSizeOfImage;
    this->isTrimmedRectSet = true;
}


