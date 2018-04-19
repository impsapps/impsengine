//
//  IABuffer.h
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on 08.08.2015.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#ifndef ImpsEngineAndroid_IABuffer_h
#define ImpsEngineAndroid_IABuffer_h

#include "IAOpenGLHeaders.h"
#include "IAOpenGLResourceDelegate.h"

typedef struct{
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
