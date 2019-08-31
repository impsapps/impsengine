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
#ifdef DEBUG
    GLint status = 0;
    glGetShaderiv(this->shaderId, GL_COMPILE_STATUS, &status);
    if (status == 0){
        GLint logLength;
        glGetShaderiv(this->shaderId, GL_INFO_LOG_LENGTH, &logLength);
        GLchar infoLog[logLength+1];
        glGetShaderInfoLog(this->shaderId, logLength, NULL, infoLog);
        infoLog[logLength] = '\0';
        logError("%s", infoLog);
    }
#endif
    glAssert();
}

GLuint IAShader_getShaderId(IAShader * this){
    return this->shaderId;
}


void IAShader_destroyOpenGLResources(IAShader * this){
	glDeleteShader(this->shaderId);
	this->shaderId = 0;
}
