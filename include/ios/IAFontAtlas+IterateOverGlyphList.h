//
//  IAFontAtlas+IterateOverGlyphList.h
//  OpenGL
//
//  Created by Konstantin Merker on 25/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAFontAtlas_IterateOverGlyphList_h
#define IAFontAtlas_IterateOverGlyphList_h

#include "IAFontAtlas.h"

void IAFontAtlas_iterateOverGlyphesForTextAtBaselineLeft(IAFontAtlas *, const char * text, IAPoint left, void * data, void (*onGlyph)(void * data, IAGlyph * glyph));
void IAFontAtlas_iterateOverGlyphesForTextAtBaselineCenter(IAFontAtlas *, const char * text, IAPoint center, void * data, void (*onGlyph)(void * data, IAGlyph * glyph));
void IAFontAtlas_iterateOverGlyphesForTextAtBaselineRight(IAFontAtlas *, const char * text, IAPoint right, void * data, void (*onGlyph)(void * data, IAGlyph * glyph));
void IAFontAtlas_iterateOverGlyphesForTextAtBaseline(IAFontAtlas *, const char * text, IAPoint pointAtBaseline, IATextAlignment alignment, void * data, void (*onGlyph)(void * data, IAGlyph * glyph));

void IAFontAtlas_iterateOverGlyphesForTextRelativelyAtMiddlelineLeft(IAFontAtlas *, const char * text, IAPoint left, void * data, void (*onGlyph)(void * data, IAGlyph * glyph));
void IAFontAtlas_iterateOverGlyphesForTextRelativelyAtMiddlelineCenter(IAFontAtlas *, const char * text, IAPoint center, void * data, void (*onGlyph)(void * data, IAGlyph * glyph));
void IAFontAtlas_iterateOverGlyphesForTextRelativelyAtMiddlelineRight(IAFontAtlas *, const char * text, IAPoint right, void * data, void (*onGlyph)(void * data, IAGlyph * glyph));
void IAFontAtlas_iterateOverGlyphesForTextRelativelyAtMiddleline(IAFontAtlas *, const char * text, IAPoint pointAtMiddleline, IATextAlignment alignment, void * data, void (*onGlyph)(void * data, IAGlyph * glyph));

#endif
