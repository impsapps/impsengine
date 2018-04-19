//
//  IATextureSelection.c
//  OpenGL
//
//  Created by Konstantin Merker on 26/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IATextureSelection.h"

#define CLASSNAME "IATextureSelection"


IATextureSelection IATextureSelection_make(IARect selectionRect, bool isRotated, IASize baseSizeOfTexture){
    return (IATextureSelection){
        .selectionRect = selectionRect,
        .isRotated = isRotated,
        .baseSizeOfTexture = baseSizeOfTexture
    };
}

IATextureSelection IATextureSelection_makeDefault(IASize baseSizeOfTexture){
    return (IATextureSelection){
        .selectionRect = IARect_make(0.0f, 0.0f, baseSizeOfTexture.width, baseSizeOfTexture.height),
        .isRotated = false,
        .baseSizeOfTexture = baseSizeOfTexture
    };
}

