#include "IALibrary.h"
#include "IAOpenGLConstants.h"
#include "IAOpenGLHeaders.h"
#include "IAOpenGLAssert.h"

#define CLASSNAME "IAOpenGLConstants"

static GLint maxCombinedTextureImageUnits;
static GLint maxTextureSize;

void IAOpenGLConstants_commence(){
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxCombinedTextureImageUnits);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
    glAssert();
}

GLint IAOpenGLConstants_getMaxCombinedTextureImageUnits(){
    return maxCombinedTextureImageUnits;
}

GLint IAOpenGLConstants_getMaxTextureSize(){
    return maxTextureSize;
}

void IAOpenGLConstants_terminate(){
    
}


