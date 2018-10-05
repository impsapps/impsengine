#include "IALibrary.h"
#include "IAColorableFontAtlas.h"

#define CLASSNAME "IAColorableFontAtlas"

void IAColorableFontAtlas_preDrawGlyph(IAColorableFontAtlas * this, IAGlyph * glyph);


void IAColorableFontAtlas_init(IAColorableFontAtlas * this, IABitmapManager * bitmapManager){
    IAFontAtlas_initWithCustomPreDrawGlyphFunction((IAFontAtlas *) this, bitmapManager, this, (void (*)(void *, IAGlyph *)) IAColorableFontAtlas_preDrawGlyph);
    this->color = IAColor_make(255, 255, 255, 255);
}

void IAColorableFontAtlas_setColor(IAColorableFontAtlas * this, IAColor color){
    this->color = color;
}

void IAColorableFontAtlas_preDrawGlyph(IAColorableFontAtlas * this, IAGlyph * glyph){
    IAGlyph_setColor(glyph, this->color);
}

void IAColorableFontAtlas_deinit(IAColorableFontAtlas * this){
    IAFontAtlas_deinit((IAFontAtlas *) this);
}


