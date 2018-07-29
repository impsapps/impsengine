//
//  IABuffer.c
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on 08.08.2015.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IALibrary.h"
#include "IABuffer.h"
#include "IAOpenGLResourceManager.h"
#include "IAOpenGLAssert.h"

#include <string.h>

#define CLASSNAME "IABuffer"

static GLenum CURRENT_GL_ELEMENT_ARRAY_BUFFER = GL_NONE;
static GLenum CURRENT_GL_ARRAY_BUFFER = GL_NONE;

void IABuffer_makeOpenGLResourceDelegate(IABuffer * this);

void IABuffer_createOpenGLResource(IABuffer * this);
void IABuffer_destroyOpenGLResource(IABuffer * this);

void IABuffer_bufferData(IABuffer * this);


void IABuffer_onNewOpenGLContext(){
    CURRENT_GL_ELEMENT_ARRAY_BUFFER = GL_NONE;
    CURRENT_GL_ARRAY_BUFFER = GL_NONE;
}

void IABuffer_init(IABuffer * this, GLenum target, size_t size, GLvoid * data, GLenum usage){
    this->base = IAObject_make(this);
    this->bufferId = 0;
	this->target = target;
	this->size = size;
	this->data = IA_malloc(size);
	memcpy(this->data, data, size);
	this->usage = usage;
    
    IABuffer_makeOpenGLResourceDelegate(this);
	IAOpenGLResourceManager_registerOpenGLResourceDelegate(&this->delegate);
    glAssert();
    IA_incrementInitCount();
}

void IABuffer_initCopy(IABuffer * this, const IABuffer * bufferToCopy){
    this->base = IAObject_make(this);
    this->bufferId = 0;
    this->target = bufferToCopy->target;
    this->size = bufferToCopy->size;
    this->data = IA_malloc(this->size);
    memcpy(this->data, bufferToCopy->data, this->size);
    this->usage = bufferToCopy->usage;
    
    IABuffer_makeOpenGLResourceDelegate(this);
    IAOpenGLResourceManager_registerOpenGLResourceDelegate(&this->delegate);
    glAssert();
    IA_incrementInitCount();
}

void IABuffer_makeOpenGLResourceDelegate(IABuffer * this){
    IAOpenGLResourceDelegateAttributes arguments;
    IAOpenGLResourceDelegateAttributes_make(&arguments, this);
    IAOpenGLResourceDelegateAttributes_setCreateResourcesFunction(&arguments, (void(*)(void * correspondingObject)) IABuffer_createOpenGLResource);
    IAOpenGLResourceDelegateAttributes_setDestroyResourcesFunction(&arguments, (void(*)(void * correspondingObject)) IABuffer_destroyOpenGLResource);
    IAOpenGLResourceDelegate_make(&this->delegate, &arguments);
}

void IABuffer_createOpenGLResource(IABuffer * this){
	glGenBuffers(1, &(this->bufferId));
    glAssert();
	IABuffer_use(this);
    glAssert();
	IABuffer_bufferData(this);
    glAssert();
}

void IABuffer_destroyOpenGLResource(IABuffer * this){
	glDeleteBuffers(1, &(this->bufferId));
	this->bufferId = 0;
}

void IABuffer_updateData(IABuffer * this, size_t size, GLvoid * data, GLenum usage){
	if(size != this->size){
		this->size = size;
		this->data = IA_realloc(this->data, size);
	}
	memcpy(this->data, data, size);
	this->usage = usage;
	bool isSurfaceCreated = IAOpenGLResourceManager_isSurfaceCreated();
	if(isSurfaceCreated){
		IABuffer_use(this);
		IABuffer_bufferData(this);
	}
}

void IABuffer_use(const IABuffer * this){
    if (this->target == GL_ARRAY_BUFFER) {
        if (this->bufferId != CURRENT_GL_ARRAY_BUFFER) {
            CURRENT_GL_ARRAY_BUFFER = this->bufferId;
            glBindBuffer(this->target, this->bufferId);
        }
    }else{
        if (this->bufferId != CURRENT_GL_ELEMENT_ARRAY_BUFFER) {
            CURRENT_GL_ELEMENT_ARRAY_BUFFER = this->bufferId;
            glBindBuffer(this->target, this->bufferId);
        }
    }
}

void IABuffer_bufferData(IABuffer * this){
	glBufferData(this->target, this->size, this->data, this->usage);
    glAssert();
}

void IABuffer_deinit(IABuffer * this){
	IAOpenGLResourceManager_unregisterOpenGLResourceDelegate(&this->delegate);
	IA_free(this->data);
    IA_decrementInitCount();
}

