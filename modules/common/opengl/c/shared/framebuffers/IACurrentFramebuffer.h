#ifndef IACurrentFramebuffer_h
#define IACurrentFramebuffer_h

#include "IAOpenGLHeaders.h"
#include <stdbool.h>

void IACurrentFramebuffer_set(GLuint frameBuffer);
bool IACurrentFramebuffer_is(GLuint frameBuffer);

#endif
