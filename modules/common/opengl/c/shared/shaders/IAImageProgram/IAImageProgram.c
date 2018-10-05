#include "IALibrary.h"
#include "IAImageProgram.h"
#include "IAOpenGLAssert.h"

#define CLASSNAME "IAImageProgram"


static const char * vertexShaderCode =
"attribute vec2 position;"
"attribute vec2 texturePosition;"
"attribute vec4 leftTopWidthHeight;"
"attribute vec4 ip_multiplicator;"
"varying vec2 ip_tempTexturePosition;"
"varying vec4 ip_tempMultiplicator;"
"void main() {"
"  gl_Position.x = position.x * leftTopWidthHeight[2] + leftTopWidthHeight[0];"
"  gl_Position.y = position.y * leftTopWidthHeight[3] - leftTopWidthHeight[1];"
"  gl_Position.z = 0.0;"
"  gl_Position.w = 1.0;"
"  ip_tempTexturePosition = texturePosition;"
"  ip_tempMultiplicator = ip_multiplicator;"
"}";

static const char * fragmentShaderCode =
"precision mediump float;"
"varying vec2 ip_tempTexturePosition;"
"varying vec4 ip_tempMultiplicator;"
"uniform sampler2D ip_textureSampler;"
"void main() {"
"  gl_FragColor = texture2D( ip_textureSampler, ip_tempTexturePosition) * ip_tempMultiplicator;"
"}";


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


