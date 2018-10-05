#ifndef IAShader_h
#define IAShader_h

#include "IAOpenGLHeaders.h"
#include "IAString.h"

typedef struct{
    //@extend
    IAObject base;
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
