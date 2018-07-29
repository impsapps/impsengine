//
//  IAProgram.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 31.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAProgram.h"
#include "IAOpenGLResourceManager.h"
#include "IAOpenGLAssert.h"


#define CLASSNAME "IAProgram"


void IAProgram_createOpenGLResources(IAProgram * this);
void IAProgram_stopUsingCurrentProgram();
void IAProgram_destroyOpenGLResources(IAProgram * this);

void IAProgram_releaseAttribute(IAProgramAttribute * attribute);


static IAProgram * currentProgram = NULL;


void IAProgram_onNewOpenGLContext(){
    currentProgram = NULL;
}

void IAProgram_init(IAProgram * this, const char * vertexShaderCode, const char * fragmentShaderCode, void (*glBindAttributeLocations)(GLuint programId)){
    glAssert();
    this->base = IAObject_make(this);
	this->programId = 0;
	this->vertexShader = IAShader_new(GL_VERTEX_SHADER, vertexShaderCode);
	this->fragmentShader = IAShader_new(GL_FRAGMENT_SHADER, fragmentShaderCode);
	this->attributes = IAArrayList_new(8);
    this->glBindAttributeLocations = glBindAttributeLocations;

    IAOpenGLResourceDelegateAttributes arguments;
    IAOpenGLResourceDelegateAttributes_make(&arguments, this);
    IAOpenGLResourceDelegateAttributes_setCreateResourcesFunction(&arguments, (void(*)(void * correspondingObject)) IAProgram_createOpenGLResources);
    IAOpenGLResourceDelegateAttributes_setDestroyResourcesFunction(&arguments, (void(*)(void * correspondingObject)) IAProgram_destroyOpenGLResources);
    IAOpenGLResourceDelegate_make(&this->delegate, &arguments);
    glAssert();
	IAOpenGLResourceManager_registerOpenGLResourceDelegate(&this->delegate);
    glAssert();
    IANotificationEvent_init(&this->linkingComplete);
    IA_incrementInitCount();
}

void IAProgram_createOpenGLResources(IAProgram * this){
	IAShader_createOpenGLResources(this->vertexShader);
	IAShader_createOpenGLResources(this->fragmentShader);
	this->programId = glCreateProgram();
    this->glBindAttributeLocations(this->programId);
    
	glAttachShader(this->programId, IAShader_getShaderId(this->vertexShader));
	glAttachShader(this->programId, IAShader_getShaderId(this->fragmentShader));
	glLinkProgram(this->programId);
    IANotificationEvent_notify(&this->linkingComplete);
    glAssert();
}

void IAProgram_registerDynamicAttribute(IAProgram * this, GLint attributeLocation){
    IAProgramAttribute * attribute = IA_malloc(sizeof(IAProgramAttribute));
    attribute->attributeLocation = attributeLocation;
    IAArrayList_add(this->attributes, attribute);
}

GLint IAProgram_getAttributeLocation(IAProgram * this, const GLchar * name){
    GLint location = glGetAttribLocation(this->programId, name);
    return location;
}

GLint IAProgram_getUniformLocation(IAProgram * this, const GLchar * name){
    return glGetUniformLocation(this->programId, name);
}

bool IAProgram_isEqual(IAProgram * this, IAProgram * program2){
    if(this == NULL || program2 == NULL){
        if(this == program2){
            return true;
        }else{
            return false;
        }
    }else{
        if (this->programId == program2->programId) {
            return true;
        }else{
            return false;
        }
    }
}

void IAProgram_use(IAProgram * this){
    if (this != currentProgram) {
        IAProgram_stopUsingCurrentProgram();
        glUseProgram(this->programId);
        IAProgramAttribute * attribute;
        foreach (attribute in arrayList(this->attributes)){
            glEnableVertexAttribArray(attribute->attributeLocation);
        }
        currentProgram = this;
    }
}

void IAProgram_stopUsingCurrentProgram(){
    if (currentProgram != NULL) {
        IAProgramAttribute * attribute;
        foreach (attribute in arrayList(currentProgram->attributes)){
            glDisableVertexAttribArray(attribute->attributeLocation);
        }
        currentProgram = NULL;
    }
}

void IAProgram_destroyOpenGLResources(IAProgram * this){
	if (IAProgram_isEqual(this, currentProgram)) {
	    IAProgram_stopUsingCurrentProgram();
	}
	glDeleteProgram(this->programId);
	IAShader_destroyOpenGLResources(this->vertexShader);
	IAShader_destroyOpenGLResources(this->fragmentShader);
}

void IAProgram_deinit(IAProgram * this){
	IAOpenGLResourceManager_unregisterOpenGLResourceDelegate(&this->delegate);
	IAShader_release(this->vertexShader);
	IAShader_release(this->fragmentShader);
    IAArrayList_callFunctionOnAllObjects(this->attributes, (void (*)(void *)) IAProgram_releaseAttribute);
    IAArrayList_release(this->attributes);
    IANotificationEvent_deinit(&this->linkingComplete);
    IA_decrementInitCount();
}

void IAProgram_releaseAttribute(IAProgramAttribute * attribute){
    IA_free(attribute);
}
