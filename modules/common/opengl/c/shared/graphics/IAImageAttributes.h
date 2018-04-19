//
//  IAImageAttributes.h
//  OpenGL
//
//  Created by Konstantin Merker on 26/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAImageAttributes_h
#define IAImageAttributes_h

#include "IATexture.h"
#include "IATextureSelection.h"

typedef struct{
    //@get
    IATexture * texture;
    //@get
    IATextureSelection textureSelection;
    //@get
    IARect trimmedRect;
    //@get
    IASize originalSizeOfImageForTrimmedRect;
    //@get
    bool isTrimmedRectSet;
} IAImageAttributes;


void IAImageAttributes_make(IAImageAttributes *, IATexture * texture, IATextureSelection textureSelection);

void IAImageAttributes_setTrimmedRect(IAImageAttributes *, IARect trimmedRect, IASize originalSizeOfImage);

#include "IAImageAttributes+Generated.h"

#endif
