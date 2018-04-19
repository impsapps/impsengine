//
//  IAProgram.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 31.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IAProgram_h
#define ImpsEngineiOS_IAProgram_h

#include <stdbool.h>

#include "IAArrayList.h"
#include "IAShader.h"
#include "IAOpenGLHeaders.h"
#include "IAOpenGLResourceDelegate.h"
#include "IANotificationEvent.h"

typedef struct{
    GLint attributeLocation;
} IAProgramAttribute;

typedef struct{
    GLuint programId;
    IAShader * vertexShader;
    IAShader * fragmentShader;
    IAArrayList * attributes;
    void (*glBindAttributeLocations)(GLuint programId);
    IAOpenGLResourceDelegate delegate;
    //@register
    IANotificationEvent linkingComplete;
} IAProgram;


void IAProgram_onNewOpenGLContext();

void IAProgram_init(IAProgram *, const char * vertexShaderCode, const char * fragmentShaderCode, void (*glBindAttributeLocations)(GLuint programId));

//register all dynamic attributes before you call program_use
void IAProgram_registerDynamicAttribute(IAProgram *, GLint attributeLocation);

GLint IAProgram_getAttributeLocation(IAProgram *, const GLchar * name);
GLint IAProgram_getUniformLocation(IAProgram *, const GLchar * name);

bool IAProgram_isEqual(IAProgram *, IAProgram * program2);

void IAProgram_use(IAProgram *);

void IAProgram_deinit(IAProgram *);

#include "IAProgram+Generated.h"

#endif
