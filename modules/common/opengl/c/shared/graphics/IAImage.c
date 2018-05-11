//
//  IAImage.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 16.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IATextureSelection.h"
#include "IALibrary.h"
#include "IAImage.h"
#include "IAImageProgramSingleton.h"
#include "IAOpenGLAssert.h"
#include "IAAllocationTracker.h"

#define CLASSNAME "IAImage"


static void IAImage_transformRectToRender(const IAImage * this, IARect * rectToTransform);

static void IAImage_setupRendering(const IAImage * this, IARect rectToRender);

static IAImageProgram * IAImage_setupImageProgram(const IAImage * this);

static const size_t sizeOfArrayBuffer = sizeof(GLfloat) * 16;
static const GLenum usage = GL_STATIC_DRAW;


void IAImage_init(IAImage * this, const IAImageAttributes * attributes){
    IAGraphicRect_make((IAGraphicRect *) this, (void (*)(const IAGraphicRect *, IARect *)) IAImage_transformRectToRender, (void (*)(const IAGraphicRect *, IARect)) IAImage_setupRendering);
    this->texture = IAImageAttributes_getTexture(attributes);
    assert(this->texture != NULL && "IAImage_init: No texture specified in IAImageAttributes! Please set a texture!");

    IATextureSelection textureSelection = IAImageAttributes_getTextureSelection(attributes);
    IATextureSelectionData textureSelectionData;
    IATextureSelectionData_make(&textureSelectionData, textureSelection);
    const GLfloat * values = IATextureSelectionData_getValues(&textureSelectionData);
    GLfloat bufferData[16];
    bufferData[0] = 0.0f;
    bufferData[1] = 0.0f;
    bufferData[2] = values[0];
    bufferData[3] = values[1];
    bufferData[4] = 0.0f;
    bufferData[5] = -1.0f;
    bufferData[6] = values[2];
    bufferData[7] = values[3];
    bufferData[8] = 1.0f;
    bufferData[9] = -1.0f;
    bufferData[10] = values[4];
    bufferData[11] = values[5];
    bufferData[12] = 1.0f;
    bufferData[13] = 0.0f;
    bufferData[14] = values[6];
    bufferData[15] = values[7];
    IAArrayBuffer_init(&this->arrayBuffer, sizeOfArrayBuffer, bufferData, usage);
    
    this->alpha = 255;
    this->overlayingColor = IAColor_make(255, 255, 255, 255);
    
    if (IAImageAttributes_isTrimmedRectSet(attributes)){
        IASize originalSizeOfImage = IAImageAttributes_getOriginalSizeOfImageForTrimmedRect(attributes);
        IARect trimmedRect = IAImageAttributes_getTrimmedRect(attributes);
        IATrimmedRect_make(&this->trimmedRect, originalSizeOfImage, trimmedRect);
        this->hasTrimmedRect = true;
        this->originalSize = originalSizeOfImage;
    }else{
        this->hasTrimmedRect = false;
        this->originalSize = textureSelection.selectionRect.size;
        if (textureSelection.isRotated){
            swap(this->originalSize.width, this->originalSize.height);
        }
    }
    
    IASize defaultSize = IAImage_getOriginalSize(this);
	IAImage_setSize(this, defaultSize);
    IA_increaseAllocationCount();
}

void IAImage_initCopy(IAImage * this, const IAImage * imageToCopy){
    IAGraphicRect_makeCopy((IAGraphicRect *) this, (const IAGraphicRect *) imageToCopy);
    this->texture = imageToCopy->texture;
    IAArrayBuffer_initCopy(&this->arrayBuffer, &imageToCopy->arrayBuffer);
    
    this->trimmedRect = imageToCopy->trimmedRect;
    this->hasTrimmedRect = imageToCopy->hasTrimmedRect;
    
    this->alpha = imageToCopy->alpha;
    this->overlayingColor = imageToCopy->overlayingColor;
    
    this->originalSize = imageToCopy->originalSize;
    IA_increaseAllocationCount();
}

void IAImage_setAlpha(IAImage * this, int alpha){
    this->alpha = alpha;
}

void IAImage_setOverlayingColor(IAImage * this, IAColor overlayingColor){
    assert(overlayingColor.alpha == 255 && "Overlaying color's alpha must always be 255.");
    this->overlayingColor = overlayingColor;
}

void IAImage_setSizeWithFixedHeight(IAImage * this, float fixedHeight){
    IASize originalSize = IAImage_getOriginalSize(this);
    IASize size = IASize_makeWithFixedHeight(originalSize, fixedHeight);
    IADrawableRect_setSize((IADrawableRect *) this, size);
}

void IAImage_setSizeWithFixedWidth(IAImage * this, float fixedWidth){
    IASize originalSize = IAImage_getOriginalSize(this);
    IASize size = IASize_makeWithFixedWidth(originalSize, fixedWidth);
    IADrawableRect_setSize((IADrawableRect *) this, size);
}

void IAImage_flipHorizontally(IAImage * this){
    const GLvoid * data = IAArrayBuffer_getData(&this->arrayBuffer);
    GLfloat newData[16];
    memcpy(newData, data, sizeOfArrayBuffer);
    swap(newData[2], newData[14]);
    swap(newData[3], newData[15]);
    swap(newData[6], newData[10]);
    swap(newData[7], newData[11]);
    IAArrayBuffer_updateData(&this->arrayBuffer, sizeOfArrayBuffer, newData, usage);
    if (this->hasTrimmedRect) {
        IATrimmedRect_flipHorizontally(&this->trimmedRect);
    }
    
}

void IAImage_flipVertically(IAImage * this){
    const GLvoid * data = IAArrayBuffer_getData(&this->arrayBuffer);
    GLfloat newData[16];
    memcpy(newData, data, sizeOfArrayBuffer);
    swap(newData[2], newData[6]);
    swap(newData[3], newData[7]);
    swap(newData[10], newData[14]);
    swap(newData[11], newData[15]);
    IAArrayBuffer_updateData(&this->arrayBuffer, sizeOfArrayBuffer, newData, usage);
    if (this->hasTrimmedRect) {
        IATrimmedRect_flipVertically(&this->trimmedRect);
    }
}

IASize IAImage_getOriginalSize(IAImage * this){
    return this->originalSize;
}

IATexture * IAImage_getTexture(IAImage * this){
    return this->texture;
}

IARect IAImage_getTrimmedRect(IAImage * this) {
	IARect trimmedRect;
	if (this->hasTrimmedRect) {
		trimmedRect = this->trimmedRect.trimmedRect;
	} else {
		trimmedRect = IARect_make(0.0f, 0.0f, this->originalSize.width, this->originalSize.height);
	}
	return trimmedRect;
}

void IAImage_deactivateTrimmedRect(IAImage * this) {
	if (this->hasTrimmedRect) {
		IARect originalRect = IARect_makeWithLeftTopPointAndSize(IAPoint_ZERO, this->originalSize);
		IARect trimmedRect = IATrimmedRect_trimRect(&this->trimmedRect, originalRect);
		this->originalSize = trimmedRect.size;
	}
	this->hasTrimmedRect = false;
}

void IAImage_transformRectToRender(const IAImage * this, IARect * rectToTransform){
    if (this->hasTrimmedRect) {
        *rectToTransform = IATrimmedRect_trimRect(&this->trimmedRect, *rectToTransform);
    }
}

static void IAImage_setupRendering(const IAImage * this, IARect rectToRender){
    IATexture_use(this->texture);
    glAssert();
    IAImageProgram * imageProgram = IAImage_setupImageProgram(this);
    glAssert();
    IAArrayBuffer_use(&this->arrayBuffer);
    glAssert();
    glVertexAttribPointer(IAImageProgram_getPositionLocation(imageProgram), 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);
    glAssert();
    glVertexAttribPointer(IAImageProgram_getTexturePositionLocation(imageProgram), 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void *) (sizeof(GLfloat) * 2));
    glAssert();
    glUniform1i(IAImageProgram_getTextureSampler2DLocation(imageProgram), IATexture_getSampler2DValue(this->texture));
    glAssert();
    glVertexAttrib4f(IAImageProgram_getLeftTopWidthHeight(imageProgram), rectToRender.origin.x, rectToRender.origin.y, rectToRender.size.width, rectToRender.size.height);
    glAssert();
}

static IAImageProgram * IAImage_setupImageProgram(const IAImage * this){
    IAImageProgram * program = IAImageProgramSingleton_getProgram();
    IAImageProgram_use(program);
    glAssert();
    
    GLfloat alpha = this->alpha / 255.0f;
    GLfloat red = this->overlayingColor.red / 255.0f * alpha;
    GLfloat green = this->overlayingColor.green / 255.0f * alpha;
    GLfloat blue = this->overlayingColor.blue / 255.0f * alpha;
    glVertexAttrib4f(IAImageProgram_getMultiplicatorLocation(program), red, green, blue, alpha);
    glAssert();
    return program;
}

void IAImage_deinit(IAImage * this){
    IAArrayBuffer_deinit(&this->arrayBuffer);
    IA_decreaseAllocationCount();
}


