//
//  IAColorRect.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 06.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAColorRect.h"
#include "IAColorRectProgramSingleton.h"
#include "IAOpenGLAssert.h"

#define CLASSNAME "IAColorRect"


void IAColorRect_transformRectToRender(const IAColorRect * this, IARect * rectToTransform);

void IAColorRect_setupRendering(const IAColorRect * this, IARect rectToRender);


void IAColorRect_init(IAColorRect * this, IAColor color){
    IAGraphicRect_make((IAGraphicRect *) this, (void (*)(const IAGraphicRect *, IARect *)) IAColorRect_transformRectToRender, (void (*)(const IAGraphicRect *, IARect)) IAColorRect_setupRendering);
    
    GLfloat bufferData[8];
    bufferData[0] = 0.0f;
    bufferData[1] = 0.0f;
    bufferData[2] = 0.0f;
    bufferData[3] = -1.0f;
    bufferData[4] = 1.0f;
    bufferData[5] = -1.0f;
    bufferData[6] = 1.0f;
    bufferData[7] = 0.0f;
    IAArrayBuffer_init(&this->arrayBuffer, sizeof(GLfloat) * 8, bufferData, GL_STATIC_DRAW);
    IAColorRect_setColor(this, color);
    IA_incrementInitCount();
}

void IAColorRect_setColor(IAColorRect * this, IAColor color){
    IAColorRect_setRed(this, color.red);
    IAColorRect_setGreen(this, color.green);
    IAColorRect_setBlue(this, color.blue);
    IAColorRect_setAlpha(this, color.alpha);
}

void IAColorRect_setRed(IAColorRect * this, int red){
    this->red = red / 255.0f;
}

void IAColorRect_setGreen(IAColorRect * this, int green){
    this->green = green / 255.0f;
}

void IAColorRect_setBlue(IAColorRect * this, int blue){
    this->blue = blue / 255.0f;
}

void IAColorRect_setAlpha(IAColorRect * this, int alpha){
    this->alpha = alpha / 255.0f;
}

void IAColorRect_transformRectToRender(const IAColorRect * this, IARect * rectToTransform){
}

void IAColorRect_setupRendering(const IAColorRect * this, IARect rectToRender){
    IAColorRectProgram * colorRectProgram = IAColorRectProgramSingleton_getColorRectProgram();
    IAColorRectProgram_use(colorRectProgram);

    IAArrayBuffer_use(&this->arrayBuffer);
    
	float alpha = this->alpha;
	float premultipliedRed = this->red * alpha;
	float premultipliedGreen = this->green * alpha;
	float premultipliedBlue = this->blue * alpha;

    glVertexAttribPointer(IAColorRectProgram_getPositionLocation(colorRectProgram), 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (void*)(0));
    glVertexAttrib4f(IAColorRectProgram_getColorLocation(colorRectProgram), premultipliedRed, premultipliedGreen, premultipliedBlue, alpha);
    glVertexAttrib4f(IAColorRectProgram_getLeftTopWidthHeight(colorRectProgram), rectToRender.origin.x, rectToRender.origin.y, rectToRender.size.width, rectToRender.size.height);
    glAssert();
}

void IAColorRect_deinit(IAColorRect * this){
    IAArrayBuffer_deinit(&this->arrayBuffer);
    IA_decrementInitCount();
}


