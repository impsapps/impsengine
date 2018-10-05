#include "IALibrary.h"
#include "IAArrayBuffer.h"

#define CLASSNAME "IAArrayBuffer"


void IAArrayBuffer_init(IAArrayBuffer * this, size_t size, GLvoid * data, GLenum usage){
	IABuffer_init((IABuffer *) this, GL_ARRAY_BUFFER, size, data, usage);
}

void IAArrayBuffer_initCopy(IAArrayBuffer * this, const IAArrayBuffer * bufferToCopy){
    IABuffer_initCopy((IABuffer *) this, (const IABuffer *) bufferToCopy);
}

void IAArrayBuffer_deinit(IAArrayBuffer * this){
    IABuffer_deinit((IABuffer *) this);
}


