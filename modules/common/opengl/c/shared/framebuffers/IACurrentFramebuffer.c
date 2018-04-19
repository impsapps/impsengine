//
//  IACurrentFramebuffer.c
//  OpenGL
//
//  Created by Konstantin Merker on 13.04.18.
//  Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IACurrentFramebuffer.h"

static GLuint frameBuffer;

void IACurrentFramebuffer_set(GLuint frameBufferTemp){
    frameBuffer = frameBufferTemp;
}

bool IACurrentFramebuffer_is(GLuint frameBufferTemp){
    return frameBuffer == frameBufferTemp;
}

