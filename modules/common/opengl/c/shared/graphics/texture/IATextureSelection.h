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
