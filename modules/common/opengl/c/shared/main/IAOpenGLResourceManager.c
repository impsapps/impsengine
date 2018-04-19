//
//  IAOpenGLResourceManager.c
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on 01.08.2015.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IALibrary.h"
#include "IAOpenGLResourceManager.h"
#include "IAOpenGLAssert.h"
#include "IAOpenGLResourceEvent.h"

#define CLASSNAME "IAOpenGLResourceManager"

static IAOpenGLResourceEvent * event = NULL;
static bool surfaceCreated = false;

void IAOpenGLResourceManager_commence(void){
    event = IAOpenGLResourceEvent_new();
    glAssert();
}

void IAOpenGLResourceManager_registerOpenGLResourceDelegate(IAOpenGLResourceDelegate * delegate){
    if(surfaceCreated){
        IAOpenGLResourceDelegate_createResources(delegate);
    }
    IAOpenGLResourceEvent_register(event, delegate);
}

void IAOpenGLResourceManager_unregisterOpenGLResourceDelegate(IAOpenGLResourceDelegate * delegate){
    if(surfaceCreated){
        IAOpenGLResourceDelegate_destroyResources(delegate);
    }
    IAOpenGLResourceEvent_unregister(event, delegate);
}

void IAOpenGLResourceManager_onSurfaceCreated(){
    if (surfaceCreated == false) {
        surfaceCreated = true;
    }
    IAOpenGLResourceEvent_createResources(event);
}

void IAOpenGLResourceManager_onSurfaceDestroyed(){
    if (surfaceCreated == true) {
        surfaceCreated = false;
        IAOpenGLResourceEvent_destroyResources(event);
    }
}

bool IAOpenGLResourceManager_isSurfaceCreated(){
    return surfaceCreated;
}

void IAOpenGLResourceManager_terminate(){
    IAOpenGLResourceEvent_release(event);
}


