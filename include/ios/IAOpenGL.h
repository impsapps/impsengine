//
//  IAOpenGL.h
//  OpenGL
//
//  Created by Konstantin Merker on 28/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAOpenGL_h
#define IAOpenGL_h

#include "IASize.h"

//You need to call commence and terminate respectively to initialize this module. These functions will call all commence and terminate functions of other classes in the module.

void IAOpenGL_commence();

void IAOpenGL_onSurfaceCreated();
void IAOpenGL_onSurfaceChanged(IASize newSurfaceSize);

void IAOpenGL_onRenderBegin();
void IAOpenGL_onRenderEnd();

void IAOpenGL_terminate();

#endif
