//
//  IAOpenGLResourceDelegate.c
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on 01.08.2015.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IALibrary.h"
#include "IAOpenGLResourceDelegate.h"

#define CLASSNAME "IAOpenGLResourceDelegate"


void IAOpenGLResourceDelegate_make(IAOpenGLResourceDelegate * this, const IAOpenGLResourceDelegateAttributes * attributes){
    *this = (IAOpenGLResourceDelegate){
        .correspondingObject = IAOpenGLResourceDelegateAttributes_getCorrespondingObject(attributes),
        .createResources = IAOpenGLResourceDelegateAttributes_getCreateResourcesFunction(attributes),
        .destroyResources = IAOpenGLResourceDelegateAttributes_getDestroyResourcesFunction(attributes)
    };
}

