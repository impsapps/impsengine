//
//  IATouch.h
//  Hit Verto
//
//  Created by Konstantin Merker on 10/03/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IATouch_h
#define Hit_Verto_IATouch_h

#include "IARect.h"

typedef struct{
    //@get
    IAPoint location;
} IATouch;


void IATouch_make(IATouch *, IAPoint location);
void IATouch_makeCopy(IATouch *, const IATouch * toCopy);

bool IATouch_isInRect(const IATouch *, IARect rect);

#include "IATouch+Generated.h"

#endif
