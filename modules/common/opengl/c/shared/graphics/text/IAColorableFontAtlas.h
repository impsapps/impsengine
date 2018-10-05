#ifndef IAColorableFontAtlas_h

#define IAColorableFontAtlas_h

#include "IAFontAtlas.h"

typedef struct{
    //@extend
    IAFontAtlas fontAtlas;
    IAColor color;
} IAColorableFontAtlas;


void IAColorableFontAtlas_init(IAColorableFontAtlas *, IABitmapManager * bitmapManager);

void IAColorableFontAtlas_setColor(IAColorableFontAtlas *, IAColor color);

void IAColorableFontAtlas_deinit(IAColorableFontAtlas *);

#include "IAColorableFontAtlas+Generated.h"

#endif
