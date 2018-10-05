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
