//
//  IAOffscreenFramebuffer.h
//  OpenGL
//
//  Created by Konstantin Merker on 13.12.17.
//Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAOffscreenFramebuffer_h
#define IAOffscreenFramebuffer_h

#include "IAOpenGLHeaders.h"
#include "IAColor.h"

/**
 * IAOffscreenFramebuffer is only intended for temporary usage as it is not persisted beween new OpenGL contexts.
 */

typedef struct{
    GLuint framebuffer;
    GLuint colorRenderbuffer;
    GLuint depthRenderbuffer;
} IAOffscreenFramebuffer;


void IAOffscreenFramebuffer_initWithRGB565AndBind(IAOffscreenFramebuffer *, int width, int height, IAColor backgroundColor);

void IAOffscreenFramebuffer_deinit(IAOffscreenFramebuffer *);

#include "IAOffscreenFramebuffer+Generated.h"

#endif
