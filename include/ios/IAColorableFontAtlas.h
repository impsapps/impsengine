//
//  IAColorableFontAtlas.h
//  Hit Verto
//
//  Created by Konstantin Merker on 10/02/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAColorableFontAtlas_h
#define Hit_Verto_IAColorableFontAtlas_h

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
