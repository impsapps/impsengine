#ifndef IABuffer_h
#define IABuffer_h

#include "IAOpenGLHeaders.h"
#include "IAOpenGLResourceDelegate.h"
#include "IAObject.h"

typedef struct{
    //@extend
    IAObject base;
	GLuint bufferId;
	GLenum target;
	GLsizeiptr size;
    //@getAsConst
	GLvoid * data;
	GLenum usage;
    IAOpenGLResourceDelegate delegate;
} IABuffer;


void IABuffer_onNewOpenGLContext();

void IABuffer_init(IABuffer *, GLenum target, size_t size, GLvoid * data, GLenum usage);
void IABuffer_initCopy(IABuffer *, const IABuffer * bufferToCopy);

void IABuffer_updateData(IABuffer *, size_t size, GLvoid * data, GLenum usage);
void IABuffer_use(const IABuffer *);

void IABuffer_deinit(IABuffer *);

#include "IABuffer+Generated.h"

#endif
