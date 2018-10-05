#ifndef IAArrayBuffer_h
#define IAArrayBuffer_h

#include "IAOpenGLHeaders.h"
#include "IABuffer.h"
#include "IAOpenGLResourceDelegate.h"

typedef struct{
    //@extend
    IABuffer buffer;
} IAArrayBuffer;


void IAArrayBuffer_init(IAArrayBuffer *, size_t size, GLvoid * data, GLenum usage);
void IAArrayBuffer_initCopy(IAArrayBuffer *, const IAArrayBuffer * bufferToCopy);

void IAArrayBuffer_deinit(IAArrayBuffer *);

#include "IAArrayBuffer+Generated.h"

#endif
