//
//  IAColorRectProgram.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 06.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAColorRectProgram.h"
#include "IAOpenGLAssert.h"

#define CLASSNAME "IAColorRectProgram"


static const char * vertexShaderCode =
"attribute vec2 position;"
"attribute vec4 leftTopWidthHeight;"
"attribute vec4 crp_color;"
"varying vec4 crp_tempColor;"
"void main() {"
"  gl_Position.x = position.x * leftTopWidthHeight[2] + leftTopWidthHeight[0];"
"  gl_Position.y = position.y * leftTopWidthHeight[3] - leftTopWidthHeight[1];"
"  gl_Position.z = 0.0;"
"  gl_Position.w = 1.0;"
"  crp_tempColor = crp_color;"
"}";

static const char * fragmentShaderCode =
"precision mediump float;"
"varying vec4 crp_tempColor;"
"void main() {"
"   gl_FragColor = crp_tempColor;"
"}";


void IAColorRectProgram_glBindAttributeLocations(GLuint programId){
    glBindAttribLocation(programId, 0, "position");
    glBindAttribLocation(programId, 1, "leftTopWidthHeight");
}

void IAColorRectProgram_onLinkingComplete(IAColorRectProgram * this){
    this->colorLocation = IAColorRectProgram_getAttributeLocation(this, "crp_color");
}

void IAColorRectProgram_init(IAColorRectProgram * this){
    IAProgram_init((IAProgram *) this, vertexShaderCode, fragmentShaderCode, IAColorRectProgram_glBindAttributeLocations);
    this->positionLocation = 0;
    this->leftTopWidthHeight = 1;
    this->colorLocation = -1;
    glAssert();
    IAColorRectProgram_registerDynamicAttribute(this, this->positionLocation);
    glAssert();
    this->linkingCompleteDelegate = (IANotificationDelegate){
        .correspondingObject = this,
        .notify = (void (*)(void *)) IAColorRectProgram_onLinkingComplete
    };
    IAColorRectProgram_registerForLinkingComplete(this, &this->linkingCompleteDelegate);
    glAssert();
}

void IAColorRectProgram_deinit(IAColorRectProgram * this){
    IAProgram_deinit((IAProgram *) this);
}


