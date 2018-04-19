//
//  IAGlyphInformation.h
//  OpenGL
//
//  Created by Konstantin Merker on 25/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAGlyphInformation_h
#define IAGlyphInformation_h

#include "IASize.h"

typedef struct{
    float originalFontSize;
    float xOffset;
    float yOffset;
    float xAdvance;
    IASize sizeOfGlyph;
    char utf8[4];
    int utf8Length;
} IAGlyphInformation;

#endif
