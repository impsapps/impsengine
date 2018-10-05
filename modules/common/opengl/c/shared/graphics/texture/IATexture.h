#ifndef IATexture_h
#define IATexture_h

#include <stdbool.h>

#include "IAOpenGLHeaders.h"
#include "IAString.h"
#include "IABitmapManager.h"
#include "IAOpenGLResourceDelegate.h"
#include "IATextureDelegate.h"

typedef struct{
    //@extend
    IAObject base;
    //@get
    IABitmap * bitmap;
    GLuint glTextureId;
    size_t initializeId;
    unsigned int indexOfCurrentUnit;
    bool needToTransportToOpenGL;
    IAOpenGLResourceDelegate openGLResourceDelegate;
    //@set+get
    IATextureDelegate * textureDelegate;
} IATexture;


void IATexture_commence(GLint maxCombinedTextureImageUnits);

void IATexture_onNewOpenGLContext();

void IATexture_init(IATexture *, IABitmap * bitmap);

void IATexture_use(IATexture *);
GLuint IATexture_getSampler2DValue(const IATexture *);

void IATexture_deinit(IATexture *);

void IATexture_terminate();

#include "IATexture+Generated.h"

#endif
