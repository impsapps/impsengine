//
//  IAOpenGL.c
//  OpenGL
//
//  Created by Konstantin Merker on 28/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAOpenGL.h"
#include "IATime.h"
#include "IACurrentFrame+Private.h"
#include "IAGraphicRect.h"
#include "IAColorRectProgramSingleton.h"
#include "IAImageProgramSingleton.h"
#include "IAOpenGLConstants.h"
#include "IAOpenGLResourceManager.h"
#include "IABitmapManagerSingleton.h"
#include "IATexture.h"
#include "IAOpenGLAssert.h"
#include "IABuffer.h"
#include "IAViewPort+Internal.h"
#include "IADefaultFramebuffer+Internal.h"
#include "IACurrentFramebuffer.h"
#include "IADrawingBounds.h"

#define CLASSNAME "IAOpenGL"

void IAOpenGL_updateCurrentTime();


void IAOpenGL_commence(){
    IATime_commenceIfNeeded();
    IAOpenGL_updateCurrentTime();
    IAOpenGLConstants_commence();
    GLint maxCombinedTextureImageUnits = IAOpenGLConstants_getMaxCombinedTextureImageUnits();
    IATexture_commence(maxCombinedTextureImageUnits);
    IAOpenGLResourceManager_commence();
    IAGraphicRect_commence();
    IAColorRectProgramSingleton_commence();
    IAImageProgramSingleton_commence();
    glAssert();
}

void IAOpenGL_updateCurrentTime(){
    uint64_t currentTime = IATime_getTimeInMilliseconds();
    IACurrentFrame_setTime(currentTime);
}

void IAOpenGL_onSurfaceCreated(){
    IATexture_onNewOpenGLContext();
    IAProgram_onNewOpenGLContext();
    IABuffer_onNewOpenGLContext();
    
    GLint framebuffer;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &framebuffer);
    IADefaultFramebuffer_setDefault(framebuffer);
    IACurrentFramebuffer_set(framebuffer);
    IAOpenGLResourceManager_onSurfaceCreated();
    glAssert();

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

void IAOpenGL_onSurfaceChanged(IASize newSurfaceSize){
    IADefaultFramebuffer_setSize(newSurfaceSize);
}

void IAOpenGL_onRenderBegin(){
    IAOpenGL_updateCurrentTime();
}

void IAOpenGL_onRenderEnd(){
    IADrawingBounds_disableBounds();
    glAssert();
}

void IAOpenGL_terminate(){
    IAGraphicRect_terminate();
    IAColorRectProgramSingleton_terminate();
    IAImageProgramSingleton_terminate();
    IAOpenGLConstants_terminate();
    IATexture_terminate();
    IAOpenGLResourceManager_terminate();
}

