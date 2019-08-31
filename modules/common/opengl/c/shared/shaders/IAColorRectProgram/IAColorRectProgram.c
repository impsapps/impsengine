#include "IALibrary.h"
#include "IAColorRectProgram.h"
#include "IAOpenGLAssert.h"

#define CLASSNAME "IAColorRectProgram"


static const char * vertexShaderCode =
"#version 130\n"
"attribute vec2 position;\n"
"attribute vec4 leftTopWidthHeight;\n"
"attribute vec4 crp_color;\n"
"varying vec4 crp_tempColor;\n"
"void main() {\n"
"  gl_Position.x = position.x * leftTopWidthHeight[2] + leftTopWidthHeight[0];\n"
"  gl_Position.y = position.y * leftTopWidthHeight[3] - leftTopWidthHeight[1];\n"
"  gl_Position.z = 0.0;\n"
"  gl_Position.w = 1.0;\n"
"  crp_tempColor = crp_color;\n"
"}\n";

static const char * fragmentShaderCode =
"#version 130\n"
"precision mediump float;\n"
"varying vec4 crp_tempColor;\n"
"void main() {\n"
"   gl_FragColor = crp_tempColor;\n"
"}\n";


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


