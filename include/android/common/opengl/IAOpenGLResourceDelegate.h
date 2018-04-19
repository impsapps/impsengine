//
//  IAOpenGLResourceDelegate.h
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on 01.08.2015.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#ifndef ImpsEngineAndroid_IAOpenGLResourceDelegate_h
#define ImpsEngineAndroid_IAOpenGLResourceDelegate_h

#include "IAOpenGLResourceDelegateAttributes.h"

//@event
typedef struct{
    void * correspondingObject;
    //@exe
    void (*createResources)(void * correspondingObject);
    //@exe
    void (*destroyResources)(void * correspondingObject);
} IAOpenGLResourceDelegate;


void IAOpenGLResourceDelegate_make(IAOpenGLResourceDelegate *, const IAOpenGLResourceDelegateAttributes * arguments);

#include "IAOpenGLResourceDelegate+Generated.h"

#endif
