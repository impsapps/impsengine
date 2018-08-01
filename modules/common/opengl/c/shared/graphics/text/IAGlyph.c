//
//  IAGlyph.c
//  Hit Verto
//
//  Created by Konstantin Merker on 21/01/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAGlyph.h"

#define CLASSNAME "IAGlyph"


void IAGlyph_drawFunction(const IAGlyph * this);


void IAGlyph_init(IAGlyph * this, IAImage * image, IAGlyphInformation glyphInformation){
    IAImage_retain(image);
    IADrawable_make((IADrawable *) this, (void (*)(const IADrawable *)) IAGlyph_drawFunction);
    this->image = image;
    this->glyphInformation = glyphInformation;
    this->customAdditionalAdvanceBetweenGlyphesInPixel = 0.0f;
    this->currentFontSize = -1.0f;
    this->currentXOffset = 0.0f;
    this->currentYOffset = 0.0f;
    this->currentXAdvance = 0.0f;
}

void IAGlyph_setCurrentFontSize(IAGlyph * this, float currentFontSize){
    if (this->currentFontSize != currentFontSize) {
        this->currentFontSize = currentFontSize;
        
        float scale = currentFontSize / this->glyphInformation.originalFontSize;
        this->currentXOffset = scale * this->glyphInformation.xOffset;
        this->currentYOffset = scale * this->glyphInformation.yOffset;
        this->currentXAdvance = scale * this->glyphInformation.xAdvance;
        IASize newSize = this->glyphInformation.sizeOfGlyph;
        newSize.width *= scale;
        newSize.height *= scale;
        IADrawableRect_setSize((IADrawableRect *) this->image, newSize);
    }
}

float IAGlyph_getCurrentFontSize(IAGlyph * this){
    return this->currentFontSize;
}

void IAGlyph_setColor(IAGlyph * this, IAColor color){
    IAImage_setAlpha(this->image, color.alpha);
    color.alpha = 255;
    IAImage_setOverlayingColor(this->image, color);
}

float IAGlyph_getWidthNeededInPixel(IAGlyph * this){
    return this->currentXAdvance;
}

float IAGlyph_getSpaceBetweenGlyphesInPixel(IAGlyph * this, IAGlyph * nextGlyph, IAHashMap * kernings, float scaleForKernings){
    float space = 0.0f;
	if (kernings) {
		char kerningKey[9];
		int kerningKeyLength = IAGlyph_toUTF8(this, kerningKey);
		kerningKeyLength += IAGlyph_toUTF8(nextGlyph, kerningKey + kerningKeyLength);
		kerningKey[kerningKeyLength] = '\0';
		float * kerningAmount = IAHashMap_get(kernings, kerningKey);
		if (kerningAmount != NULL) {
			space -= *kerningAmount * scaleForKernings;
		}
	}
    space += this->customAdditionalAdvanceBetweenGlyphesInPixel;
    return space;
}

int IAGlyph_toUTF8(IAGlyph * this, char utf8Out[4]){
    for (int i = 0; i < this->glyphInformation.utf8Length; i++) {
        utf8Out[i] = this->glyphInformation.utf8[i];
    }
    return this->glyphInformation.utf8Length;
}

void IAGlyph_setLeftTopPoint(IAGlyph * this, IAPoint point){
    point.x += this->currentXOffset;
    point.y += this->currentYOffset;
    IADrawableRect_setLeftTopPoint((IADrawableRect *) this->image, point);
}

void IAGlyph_drawFunction(const IAGlyph * this){
    IAImage_draw(this->image);
}

void IAGlyph_deinit(IAGlyph * this){
    IAImage_release(this->image);
}


