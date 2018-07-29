//
//  IAShader.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 31.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAShader.h"
#include "IAString.h"
#include "IAOpenGLAssert.h"

#define CLASSNAME "IAShader"


void IAShader_make(IAShader * this, const GLenum type, const char * sourceCode){
    this->base = IAObject_make(this);
	this->shaderId = 0;
	this->type = type;
	this->sourceCode = sourceCode;
}

void IAShader_createOpenGLResources(IAShader * this){
    glAssert();
	this->shaderId = glCreateShader(this->type);
    glShaderSource(this->shaderId, 1, &this->sourceCode, NULL);
    glCompileShader(this->shaderId);
    glAssert();
}

GLuint IAShader_getShaderId(IAShader * this){
    return this->shaderId;
}


void IAShader_destroyOpenGLResources(IAShader * this){
	glDeleteShader(this->shaderId);
	this->shaderId = 0;
}
