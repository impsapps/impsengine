#include "IALibrary.h"
#include "IAImageProgram.h"
#include "IAOpenGLAssert.h"

#define CLASSNAME "IAImageProgram"


static const char * vertexShaderCode =
"#version 130\n"
"attribute vec2 position;\n"
"attribute vec2 texturePosition;\n"
"attribute vec4 leftTopWidthHeight;\n"
"attribute vec4 ip_multiplicator;\n"
"varying vec2 ip_tempTexturePosition;\n"
"varying vec4 ip_tempMultiplicator;\n"
"void main() {\n"
"  gl_Position.x = position.x * leftTopWidthHeight[2] + leftTopWidthHeight[0];\n"
"  gl_Position.y = position.y * leftTopWidthHeight[3] - leftTopWidthHeight[1];\n"
"  gl_Position.z = 0.0;\n"
"  gl_Position.w = 1.0;\n"
"  ip_tempTexturePosition = texturePosition;\n"
"  ip_tempMultiplicator = ip_multiplicator;\n"
"}\n";

static const char * fragmentShaderCode =
"#version 130\n"
"precision mediump float;\n"
"varying vec2 ip_tempTexturePosition;\n"
"varying vec4 ip_tempMultiplicator;\n"
"uniform sampler2D ip_textureSampler;\n"
"void main() {\n"
"  gl_FragColor = texture2D( ip_textureSampler, ip_tempTexturePosition) * ip_tempMultiplicator;\n"
"}\n";


void IAImageProgram_glBindAttributeLocations(GLuint programId){
    glBindAttribLocation(programId, 0, "position");
    glBindAttribLocation(programId, 1, "leftTopWidthHeight");
    glBindAttribLocation(programId, 2, "texturePosition");
}

void IAImageProgram_onLinkingComplete(IAImageProgram * this){
    this->multiplicatorLocation = IAImageProgram_getAttributeLocation(this, "ip_multiplicator");
    this->textureSampler2DLocation = IAImageProgram_getUniformLocation(this, "ip_textureSampler");
}

void IAImageProgram_init(IAImageProgram * this){
    IAProgram_init((IAProgram *) this, vertexShaderCode, fragmentShaderCode, IAImageProgram_glBindAttributeLocations);
    glAssert();
    this->positionLocation = 0;
    this->texturePositionLocation = 2;
    this->leftTopWidthHeight = 1;
    this->textureSampler2DLocation = -1;
    this->multiplicatorLocation = -1;
    glAssert();
    IAImageProgram_registerDynamicAttribute(this, this->positionLocation);
    IAImageProgram_registerDynamicAttribute(this, this->texturePositionLocation);
    glAssert();
    this->linkingCompleteDelegate = (IANotificationDelegate){
        .correspondingObject = this,
        .notify = (void (*)(void *)) IAImageProgram_onLinkingComplete
    };
    IAImageProgram_registerForLinkingComplete(this, &this->linkingCompleteDelegate);
    glAssert();
}

void IAImageProgram_deinit(IAImageProgram * this){
    IAProgram_deinit((IAProgram *) this);
}


