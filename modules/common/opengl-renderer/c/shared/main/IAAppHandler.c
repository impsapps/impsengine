//
//  IAAppHandler.c
//  core
//
//  Created by Konstantin Merker on 11.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IALibrary.h"
#include "IALibrary+SendOnMemoryWarningNotification.h"
#include "IAAppHandler.h"
#include "IAAppHandler+Native.h"
#include "IAOpenGL.h"
#include "IAOpenGLHeaders.h"
#include "IAMultiTouch.h"
#include "IATime.h"
#include "IAApp.h"
#include "IAAppEntryPoint+Core.h"
#include "IAOpenGLAssert.h"

#define CLASSNAME "IAAppHandler"

static bool areLibrariesCommenced = false;

static IASize surfaceSize = {.width = 0.0f, .height = 0.0f};

static IAApp appDelegate;


void IAAppHandler_onAppStart(){
    IAAppAttributes attributes;
    IAAppAttributes_make(&attributes, NULL);
    IAAppEntryPoint_onAppStart(&attributes);
    IAApp_make(&appDelegate, &attributes);
}

IAApp * IAAppHandler_getAppDelegate(){
    return &appDelegate;
}

void IAAppHandler_onSurfaceCreated(){
    if(areLibrariesCommenced == false){
        IAOpenGL_commence();
        IAMultiTouch_commence();
    }
    glAssert();
    IAOpenGL_onSurfaceCreated();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);

    if(areLibrariesCommenced == false){
        IAApp_commence(&appDelegate);
        areLibrariesCommenced = true;
    }
}

void IAAppHandler_onSurfaceChanged(IASize newSurfaceSize){
    surfaceSize = newSurfaceSize;
    IAOpenGL_onSurfaceChanged(surfaceSize);
    IAApp_onSurfaceSizeChanged(&appDelegate, surfaceSize);
}

IASize IAAppHandler_getSurfaceSize(){
    return surfaceSize;
}

void IAAppHandler_render(){
    uint64_t renderTimeStart;
    if (IAApp_shouldLogRenderingPerformance(&appDelegate)){
        renderTimeStart = IATime_getTimeInMilliseconds();
    }
    IAOpenGL_onRenderBegin();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    IAApp_render(&appDelegate);
    IAOpenGL_onRenderEnd();
    if (IAApp_shouldLogRenderingPerformance(&appDelegate)){
        logInfo("Rendering finished. Time needed (in ms): %lld", IATime_getTimeInMilliseconds() - renderTimeStart);
    }
}

void IAAppHandler_switchToPausescreen(){
    IAApp_switchToPauseScreen(&appDelegate);
}

void IAAppHandler_saveGameState(){
    IAApp_saveGameState(&appDelegate);
}

void IAAppHandler_destroyResources(){
    IAApp_terminate(&appDelegate);
    
    IAMultiTouch_terminate();
    IAOpenGL_terminate();
}

void IAAppHandler_onMemoryWarning(){
    IALibrary_onMemoryWarning();
}



