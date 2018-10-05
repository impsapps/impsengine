#include "IALibrary.h"
#include "IAElementArrayBuffer.h"

#define CLASSNAME "IAElementArrayBuffer"


void IAElementArrayBuffer_init(IAElementArrayBuffer * this, size_t size, GLvoid * data, GLenum usage){
    IABuffer_init((IABuffer *) this, GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

void IAElementArrayBuffer_initCopy(IAElementArrayBuffer * this, const IAElementArrayBuffer * bufferToCopy){
    IABuffer_initCopy((IABuffer *) this, (const IABuffer *) bufferToCopy);
}

void IAElementArrayBuffer_deinit(IAElementArrayBuffer * this){
    IABuffer_deinit((IABuffer *) this);
}


