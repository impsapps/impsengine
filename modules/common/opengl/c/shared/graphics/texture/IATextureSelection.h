//
//  IATextureSelection.h
//  OpenGL
//
//  Created by Konstantin Merker on 26/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IATextureSelection_h
#define IATextureSelection_h

#include "IARect.h"

typedef struct{
    IARect selectionRect;
    bool isRotated;
    IASize baseSizeOfTexture;
} IATextureSelection;


IATextureSelection IATextureSelection_make(IARect selectionRect, bool isRotated, IASize baseSizeOfTexture);
IATextureSelection IATextureSelection_makeDefault(IASize baseSizeOfTexture);

#endif
