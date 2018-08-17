//
//  IACurrentFramebuffer.h
//  OpenGL
//
//  Created by Konstantin Merker on 13.04.18.
//  Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IACurrentFramebuffer_h
#define IACurrentFramebuffer_h

#include "IAOpenGLHeaders.h"
#include <stdbool.h>

void IACurrentFramebuffer_set(GLuint frameBuffer);
bool IACurrentFramebuffer_is(GLuint frameBuffer);

#endif
