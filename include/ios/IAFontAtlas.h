//
//  IAFontAtlas.h
//  Hit Verto
//
//  Created by Konstantin Merker on 30/01/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAFontAtlas_h
#define Hit_Verto_IAFontAtlas_h

#include "IAGlyph.h"
#include "IAHashMap.h"
#include "IAArrayList.h"
#include "IABitmapManager.h"
#include "IAFontInformation.h"
#include "IATextAlignment.h"

typedef struct{
    //@extend
    IAObject base;
    IAHashMap * glyphs;
    int currentCountOfGlyphs;
    IAHashMap * kernings;
    int currentCountOfKernings;
    IAArrayList * textures;
    IATextureDelegate textureDelegate;
    IAFontInformation * fontInformation;
    float currentSizeOfFont;
    void * correspondingObject;
    void (*preDrawGlyph)(void *, IAGlyph *);
    
    IABitmapManager * bitmapManager;
    IAArrayList bitmaps;
} IAFontAtlas;


void IAFontAtlas_init(IAFontAtlas *, IABitmapManager * bitmapManager);
void IAFontAtlas_initWithDefaultBitmapManager(IAFontAtlas *);
void IAFontAtlas_initWithCustomPreDrawGlyphFunction(IAFontAtlas *, IABitmapManager * bitmapManager, void * correspondingObject, void (*preDrawGlyph)(void *, IAGlyph *));

void IAFontAtlas_addGlyphsFromFnt(IAFontAtlas *, const char * fntResource, bool shouldPreload);

void IAFontAtlas_setCurrentFontSize(IAFontAtlas *, float currentFontSize);

void IAFontAtlas_setCustomAdditionalAdvanceBetweenGlyphesInPixel(IAFontAtlas *, float customAdditionalAdvanceBetweenGlyphesInPixel);

float IAFontAtlas_getLengthForText(IAFontAtlas *, const char * text);

bool IAFontAtlas_hasAllGlyphesForText(IAFontAtlas *, const char * text);

void IAFontAtlas_drawTextAtBaselineLeft(IAFontAtlas *, const char * text, IAPoint left);
void IAFontAtlas_drawTextAtBaselineCenter(IAFontAtlas *, const char * text, IAPoint center);
void IAFontAtlas_drawTextAtBaselineRight(IAFontAtlas *, const char * text, IAPoint right);
void IAFontAtlas_drawTextAtBaseline(IAFontAtlas *, const char * text, IAPoint pointAtBaseline, IATextAlignment alignment);

void IAFontAtlas_drawTextRelativelyAtMiddlelineLeft(IAFontAtlas *, const char * text, IAPoint left);
void IAFontAtlas_drawTextRelativelyAtMiddlelineCenter(IAFontAtlas *, const char * text, IAPoint center);
void IAFontAtlas_drawTextRelativelyAtMiddlelineRight(IAFontAtlas *, const char * text, IAPoint right);
void IAFontAtlas_drawTextRelativelyAtMiddleline(IAFontAtlas *, const char * text, IAPoint pointAtMiddleline, IATextAlignment alignment);

IAFontInformation * IAFontAtlas_getFontInformation(IAFontAtlas *);

void IAFontAtlas_deinit(IAFontAtlas *);

#include "IAFontAtlas+Generated.h"

#endif
