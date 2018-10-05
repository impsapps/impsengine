#include "IACurrentFramebuffer.h"

static GLuint frameBuffer;

void IACurrentFramebuffer_set(GLuint frameBufferTemp){
    frameBuffer = frameBufferTemp;
}

bool IACurrentFramebuffer_is(GLuint frameBufferTemp){
    return frameBuffer == frameBufferTemp;
}

