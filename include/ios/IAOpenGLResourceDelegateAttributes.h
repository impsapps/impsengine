//
//  IAOpenGLResourceDelegateAttributes.h
//  OpenGL
//
//  Created by Konstantin Merker on 26/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAOpenGLResourceDelegateAttributes_h
#define IAOpenGLResourceDelegateAttributes_h

typedef struct{
    //@get
    void * correspondingObject;
    //@set+get
    void (*createResources)(void * correspondingObject);
    //@set+get
    void (*destroyResources)(void * correspondingObject);
} IAOpenGLResourceDelegateAttributes;


void IAOpenGLResourceDelegateAttributes_make(IAOpenGLResourceDelegateAttributes *, void * correspondingObject);

#include "IAOpenGLResourceDelegateAttributes+Generated.h"

#endif
