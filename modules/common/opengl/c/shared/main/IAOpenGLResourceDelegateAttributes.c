//
//  IAOpenGLResourceDelegateAttributes.c
//  OpenGL
//
//  Created by Konstantin Merker on 26/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAOpenGLResourceDelegateAttributes.h"

#define CLASSNAME "IAOpenGLResourceDelegateAttributes"


void IAOpenGLResourceDelegateAttributes_make(IAOpenGLResourceDelegateAttributes * this, void * correspondingObject){
    *this = (IAOpenGLResourceDelegateAttributes){
        .correspondingObject = correspondingObject
    };
}


