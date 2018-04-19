//
//  IAGlyph.h
//  Hit Verto
//
//  Created by Konstantin Merker on 21/01/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAGlyph_h
#define Hit_Verto_IAGlyph_h

#include "IAImage.h"
#include "IAGlyphInformation.h"
#include "IAHashMap.h"

typedef struct{
    //@extend
    IADrawable drawable;
    IAImage * image;
    IAGlyphInformation glyphInformation;
    //@set+get
    float customAdditionalAdvanceBetweenGlyphesInPixel;
    float currentFontSize;
    float currentXOffset;
    float currentYOffset;
    float currentXAdvance;
} IAGlyph;


void IAGlyph_initAndGivePermissionForReleasingImage(IAGlyph *, IAImage * image, IAGlyphInformation glyphInformation);

void IAGlyph_setCurrentFontSize(IAGlyph *, float currentFontSize);
float IAGlyph_getCurrentFontSize(IAGlyph *);

void IAGlyph_setColor(IAGlyph *, IAColor color);

float IAGlyph_getWidthNeededInPixel(IAGlyph *);
float IAGlyph_getSpaceBetweenGlyphesInPixel(IAGlyph *, IAGlyph * nextGlyph, IAHashMap * kernings, float scaleForKernings);

int IAGlyph_toUTF8(IAGlyph *, char utf8Out[4]);

void IAGlyph_setLeftTopPoint(IAGlyph *, IAPoint point);

void IAGlyph_deinit(IAGlyph *);

#include "IAGlyph+Generated.h"

#endif
