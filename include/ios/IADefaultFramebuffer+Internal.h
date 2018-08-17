//
//  IADefaultFramebuffer+Internal.h
//  OpenGL
//
//  Created by Konstantin Merker on 16.12.17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IADefaultFramebuffer_Internal_h
#define IADefaultFramebuffer_Internal_h

#include "IAOpenGLHeaders.h"
#include "IASize.h"

void IADefaultFramebuffer_setDefault(GLuint framebuffer);
void IADefaultFramebuffer_setSize(IASize size);

#endif
