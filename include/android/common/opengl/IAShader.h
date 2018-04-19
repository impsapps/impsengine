//
//  IAShader.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 31.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IAShader_h
#define ImpsEngineiOS_IAShader_h

#include "IAOpenGLHeaders.h"
#include "IAString.h"

typedef struct{
    GLuint shaderId;
    GLenum type;
    const char * sourceCode;
}IAShader;


void IAShader_make(IAShader *, const GLenum type, const char * sourceCode);

void IAShader_createOpenGLResources(IAShader *);
GLuint IAShader_getShaderId(IAShader *);
void IAShader_destroyOpenGLResources(IAShader *);

#include "IAShader+Generated.h"

#endif
