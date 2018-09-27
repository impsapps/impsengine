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
    long identifier;
    //@get
    IAPoint location;
} IATouch;


IATouch IATouch_make(long identifier, IAPoint location);

bool IATouch_hasSameIdentifier(IATouch t1, IATouch t2);

#include "IATouch+Generated.h"

#endif
