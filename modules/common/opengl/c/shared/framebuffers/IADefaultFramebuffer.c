//
//  IADefaultFramebuffer.c
//  OpenGL
//
//  Created by Konstantin Merker on 13.12.17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IADefaultFramebuffer.h"
#include "IADefaultFramebuffer+Internal.h"
#include "IAOpenGLHeaders.h"
#include "IAViewPort+Internal.h"
#include "IACurrentFramebuffer.h"


static GLint framebuffer;
static IASize size;

void IADefaultFramebuffer_setDefault(GLuint framebufferTemp){
    framebuffer = framebufferTemp;
}

void IADefaultFramebuffer_setSize(IASize sizeTemp){
    size = sizeTemp;
    if (IACurrentFramebuffer_is(framebuffer)) {
        IAViewPort_updateFrameBufferSize(size);
    }
}

void IADefaultFramebuffer_bind(){
    if (IACurrentFramebuffer_is(framebuffer) == false) {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        IAViewPort_updateFrameBufferSize(size);
        IACurrentFramebuffer_set(framebuffer);
    }
}

