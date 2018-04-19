//
//  IATextureDelegateAttributes.h
//  OpenGL
//
//  Created by Konstantin Merker on 01/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IATextureDelegateAttributes_h
#define IATextureDelegateAttributes_h

#include "IABitmap.h"

typedef struct{
    //@get
    void * correspondingObject;
    //@set+get
    void (*onBitmapUsageBegin)(void * correspondingObject, IABitmap * bitmap);
    //@set+get
    void (*onBitmapUsageEnd)(void * correspondingObject, IABitmap * bitmap);
} IATextureDelegateAttributes;


void IATextureDelegateAttributes_make(IATextureDelegateAttributes *, void * correspondingObject);

#include "IATextureDelegateAttributes+Generated.h"

#endif
