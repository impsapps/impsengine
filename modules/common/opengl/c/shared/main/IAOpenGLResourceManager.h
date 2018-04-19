//
//  IAOpenGLResourceManager.h
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on 01.08.2015.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#ifndef ImpsEngineAndroid_IAOpenGLResourceManager_h
#define ImpsEngineAndroid_IAOpenGLResourceManager_h

#include "IAOpenGLResourceDelegate.h"

void IAOpenGLResourceManager_commence(void);

void IAOpenGLResourceManager_registerOpenGLResourceDelegate(IAOpenGLResourceDelegate * delegate);

void IAOpenGLResourceManager_unregisterOpenGLResourceDelegate(IAOpenGLResourceDelegate * delegate);

void IAOpenGLResourceManager_onSurfaceCreated();
void IAOpenGLResourceManager_onSurfaceDestroyed();

bool IAOpenGLResourceManager_isSurfaceCreated();

void IAOpenGLResourceManager_terminate();

#endif
