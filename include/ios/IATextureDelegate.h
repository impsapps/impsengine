//
//  IATextureDelegate.h
//  OpenGL
//
//  Created by Konstantin Merker on 01/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IATextureDelegate_h
#define IATextureDelegate_h

#include "IATextureDelegateAttributes.h"

typedef struct{
    void * correspondingObject;
    //@exe
    void (*onBitmapUsageBegin)(void * correspondingObject, IABitmap * bitmap);
    //@exe
    void (*onBitmapUsageEnd)(void * correspondingObject, IABitmap * bitmap);
} IATextureDelegate;


void IATextureDelegate_make(IATextureDelegate *, IATextureDelegateAttributes * attributes);

#include "IATextureDelegate+Generated.h"

#endif
