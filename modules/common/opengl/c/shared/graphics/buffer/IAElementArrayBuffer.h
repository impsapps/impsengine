#ifndef IAElementArrayBuffer_h
#define IAElementArrayBuffer_h

#include "IAOpenGLHeaders.h"
#include "IABuffer.h"

typedef struct{
    //@extend
    IABuffer buffer;
} IAElementArrayBuffer;


void IAElementArrayBuffer_init(IAElementArrayBuffer *, size_t size, GLvoid * data, GLenum usage);
void IAElementArrayBuffer_initCopy(IAElementArrayBuffer *, const IAElementArrayBuffer * bufferToCopy);

void IAElementArrayBuffer_deinit(IAElementArrayBuffer *);

#include "IAElementArrayBuffer+Generated.h"

#endif
