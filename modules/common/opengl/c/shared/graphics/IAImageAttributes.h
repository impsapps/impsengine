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
