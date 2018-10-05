#include "IALibrary.h"
#include "IATexture.h"
#include "IAOpenGLResourceManager.h"
#include "IAOpenGLAssert.h"

#define CLASSNAME "IATexture"

void IATexture_createOpenGLResources(IATexture * this);

void IATexture_transportToOpenGL(IATexture * this);

void IATexture_activateIfNeeded(IATexture * this);
bool IATexture_isStillInCurrentUnit(const IATexture * this);

void IATexture_destroyOpenGLResources(IATexture * this);


static size_t initializeId = 1;
static size_t initializeIdPerUnitLength = 0;
static size_t * initializeIdPerUnit;
static int indexOfNextUnitToUse = 0;
static GLenum currentActiveTexture = -1;


void IATexture_commence(GLint maxCombinedTextureImageUnits){
    initializeIdPerUnitLength = maxCombinedTextureImageUnits;
    initializeIdPerUnit = IA_calloc(initializeIdPerUnitLength, sizeof(size_t));
}

void IATexture_onNewOpenGLContext(){
    for (int i = 0; i < initializeIdPerUnitLength; i++) {
        initializeIdPerUnit[i] = 0;
    }
    currentActiveTexture = -1;
    indexOfNextUnitToUse = 0;
}

void IATexture_init(IATexture * this, IABitmap * bitmap){
    IABitmap_retain(bitmap);
    this->base = IAObject_make(this);
    this->bitmap = bitmap;
    this->glTextureId = 0;
    this->initializeId = initializeId;
    initializeId ++;
    this->indexOfCurrentUnit = 0;
    this->needToTransportToOpenGL = true;
    
    IAOpenGLResourceDelegateAttributes arguments;
    IAOpenGLResourceDelegateAttributes_make(&arguments, this);
    IAOpenGLResourceDelegateAttributes_setCreateResourcesFunction(&arguments, (void(*)(void * correspondingObject)) IATexture_createOpenGLResources);
    IAOpenGLResourceDelegateAttributes_setDestroyResourcesFunction(&arguments, (void(*)(void * correspondingObject)) IATexture_destroyOpenGLResources);
    IAOpenGLResourceDelegate_make(&this->openGLResourceDelegate, &arguments);
    IAOpenGLResourceManager_registerOpenGLResourceDelegate(&this->openGLResourceDelegate);
    this->textureDelegate = NULL;
    IA_incrementInitCount();
}

void IATexture_createOpenGLResources(IATexture * this){
	glGenTextures(1, &(this->glTextureId));
	this->needToTransportToOpenGL = true;
    glAssert();
}

void IATexture_use(IATexture * this){
    if (this->textureDelegate != NULL) {
        IATextureDelegate_onBitmapUsageBegin(this->textureDelegate, this->bitmap);
    }
    if (this->needToTransportToOpenGL) {
        IATexture_transportToOpenGL(this);
    }else{
        if(IATexture_isStillInCurrentUnit(this) == false){
            IATexture_activateIfNeeded(this);
            glBindTexture(GL_TEXTURE_2D, this->glTextureId);
        }
    }
    if (this->textureDelegate != NULL) {
        IATextureDelegate_onBitmapUsageEnd(this->textureDelegate, this->bitmap);
    }
}

void IATexture_transportToOpenGL(IATexture * this){
    IABitmap_createRefIfNeeded(this->bitmap);
    IATexture_activateIfNeeded(this);
    glBindTexture(GL_TEXTURE_2D, this->glTextureId);
    IABitmap_bind(this->bitmap);
    this->needToTransportToOpenGL = false;
}

void IATexture_activateIfNeeded(IATexture * this){
    if (IATexture_isStillInCurrentUnit(this) == false){
        initializeIdPerUnit[indexOfNextUnitToUse] = this->initializeId;
        this->indexOfCurrentUnit = indexOfNextUnitToUse;
        indexOfNextUnitToUse++;
        if (indexOfNextUnitToUse >= initializeIdPerUnitLength){
            indexOfNextUnitToUse = 0;
        }
    }
	GLenum glTextureNumber = GL_TEXTURE0 + this->indexOfCurrentUnit;
	if(glTextureNumber != currentActiveTexture){
		glActiveTexture(glTextureNumber);
		currentActiveTexture = glTextureNumber;
	}
}

bool IATexture_isStillInCurrentUnit(const IATexture * this){
    return initializeIdPerUnit[this->indexOfCurrentUnit] == this->initializeId;
}

GLuint IATexture_getSampler2DValue(const IATexture * this){
    debugAssert(this->indexOfCurrentUnit >= 0 && this->indexOfCurrentUnit < initializeIdPerUnitLength && "Invalid usage of IATexture!");
    return this->indexOfCurrentUnit;
}

void IATexture_destroyOpenGLResources(IATexture * this){
	glDeleteTextures(1, &(this->glTextureId));
	this->glTextureId = 0;
    this->needToTransportToOpenGL = true;
}

void IATexture_deinit(IATexture * this){
	IAOpenGLResourceManager_unregisterOpenGLResourceDelegate(&this->openGLResourceDelegate);
    IABitmap_release(this->bitmap);
    IA_decrementInitCount();
}

void IATexture_terminate(){
    initializeIdPerUnitLength = 0;
    IA_free(initializeIdPerUnit);
}


