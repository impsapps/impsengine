//
//  IAMatrix44.c
//  Hit Verto
//
//  Created by Konstantin Merker on 26/01/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IALibrary.h"
#include "IAMatrix44.h"
#include "IAMath.h"

#define CLASSNAME "IAMatrix44"


void IAMatrix44_make(IAMatrix44 * this){
    for (int i = 0; i < 16; i++) {
        this->values[i] = 0.0f;
    }
}

void IAMatrix44_makeCopy(IAMatrix44 * this, IAMatrix44 * toCopy){
    for (int i = 0; i < 16; i++) {
        this->values[i] = toCopy->values[i];
    }
}

void IAMatrix44_makeOrthographicProjection(IAMatrix44 * this, GLfloat near, GLfloat far, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom){
    IAMatrix44_make(this);
    this->values[0] = 2.0f / (right-left);
    this->values[5] = 2.0f / (top-bottom);
    this->values[10] = -2.0f / (far-near);
    
    this->values[12] = -(right+left) / (right-left);
    this->values[13] = -(top+bottom) / (top-bottom);
    this->values[14] = (far+near) / (far-near);
    this->values[15] = 1.0f;
}

void IAMatrix44_makeWithMultiplikationResult(IAMatrix44 * this, IAMatrix44 * firstFactor, IAMatrix44 * secondFactor){
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            this->values[x*4+y] = 0.0f;
            for (int i = 0; i < 4; i++) {
                this->values[x*4 + y] += firstFactor->values[i+x*4] * secondFactor->values[y+i*4];
            }
        }
    }
}

void IAMatrix44_makeTranslationMatrix(IAMatrix44 * this, GLfloat x, GLfloat y, GLfloat z){
    IAMatrix44_make(this);
    this->values[0] = 1.0f;
    this->values[5] = 1.0f;
    this->values[10] = 1.0f;
    this->values[15] = 1.0f;
    IAMatrix44_changeTranslationMatrix(this, x, y, z);
}

void IAMatrix44_makeScaleMatrix(IAMatrix44 * this, GLfloat stretchX, GLfloat stretchY, GLfloat stretchZ){
    IAMatrix44_make(this);
    this->values[15] = 1.0f;
    IAMatrix44_changeScaleMatrix(this, stretchX, stretchY, stretchZ);
}

void IAMatrix44_makeRotationXMatrix(IAMatrix44 * this, GLfloat radians){
    IAMatrix44_make(this);
    this->values[0] = 1.0f;
    this->values[15] = 1.0f;
    
    this->values[5] = cosf(radians);
    this->values[9] = sinf(radians);
    this->values[6] = -sinf(radians);
    this->values[10] = cosf(radians);
}

void IAMatrix44_makeRotationXMatrixWithDegrees(IAMatrix44 * this, GLfloat degrees){
    return IAMatrix44_makeRotationXMatrix(this, degreesToRadians(degrees));
}

void IAMatrix44_makeRotationYMatrix(IAMatrix44 * this, GLfloat radians){
    IAMatrix44_make(this);
    this->values[5] = 1.0f;
    this->values[15] = 1.0f;
    
    this->values[0] = cosf(radians);
    this->values[8] = -sinf(radians);
    this->values[2] = sinf(radians);
    this->values[10] = cosf(radians);
}

void IAMatrix44_makeRotationYMatrixWithDegrees(IAMatrix44 * this, GLfloat degrees){
    return IAMatrix44_makeRotationYMatrix(this, degreesToRadians(degrees));
}

void IAMatrix44_makeRotationZMatrix(IAMatrix44 * this, GLfloat radians){
    IAMatrix44_make(this);
    this->values[10] = 1.0f;
    this->values[15] = 1.0f;
    IAMatrix44_setRotationZ(this, radians);
}

void IAMatrix44_makeRotationZMatrixWithDegrees(IAMatrix44 * this, GLfloat degrees){
    return IAMatrix44_makeRotationZMatrix(this, degreesToRadians(degrees));
}

void IAMatrix44_makeTrimmedRect(IAMatrix44 * this, IARect trimmedRect, IASize originalSize){
    IAMatrix44_setTrimmedRect(this, trimmedRect, originalSize);
}

void IAMatrix44_makeTransformation(IAMatrix44 * this, IARect oldRect, IARect newRect){
    IAMatrix44_setTransformation(this, oldRect, newRect);
}

void IAMatrix44_makeAsIdentityMatrix(IAMatrix44 * this){
    IAMatrix44_setIdentityMatrix(this);
}

void IAMatrix44_multiplyModelMatrix(IAMatrix44 * this, IAMatrix44 * modelMatrix){
    if(modelMatrix != NULL){
        IAMatrix44 tempMatrix;
        for (int i = 0; i < 16; i++) {
            tempMatrix.values[i] = this->values[i];
        }
        IAMatrix44_makeWithMultiplikationResult(this, &tempMatrix, modelMatrix);
    }
}

void IAMatrix44_changeTranslationMatrix(IAMatrix44 * this, GLfloat x, GLfloat y, GLfloat z){
    this->values[12] = x;
    this->values[13] = y;
    this->values[14] = z;
}

void IAMatrix44_setXForTranslationMatrix(IAMatrix44 * this, GLfloat x){
    this->values[12] = x;
}

GLfloat IAMatrix44_getXForTranslationMatrix(IAMatrix44 * this){
    return this->values[12];
}

void IAMatrix44_setYForTranslationMatrix(IAMatrix44 * this, GLfloat y){
    this->values[13] = y;
}

GLfloat IAMatrix44_getYForTranslationMatrix(IAMatrix44 * this){
    return this->values[13];
}

void IAMatrix44_setZForTranslationMatrix(IAMatrix44 * this, GLfloat z){
    this->values[14] = z;
}

GLfloat IAMatrix44_getZForTranslationMatrix(IAMatrix44 * this){
    return this->values[14];
}

void IAMatrix44_changeScaleMatrix(IAMatrix44 * this, GLfloat stretchX, GLfloat stretchY, GLfloat stretchZ){
    this->values[0] = stretchX;
    this->values[5] = stretchY;
    this->values[10] = stretchZ;
}

void IAMatrix44_setStretchXForScaleMatrix(IAMatrix44 * this, GLfloat stretchX){
    this->values[0] = stretchX;
}

GLfloat IAMatrix44_getStretchXForScaleMatrix(IAMatrix44 * this){
    return this->values[0];
}

void IAMatrix44_setStretchYForScaleMatrix(IAMatrix44 * this, GLfloat stretchY){
    this->values[5] = stretchY;
}

GLfloat IAMatrix44_getStretchYForScaleMatrix(IAMatrix44 * this){
    return this->values[5];
}

void IAMatrix44_setStretchZForScaleMatrix(IAMatrix44 * this, GLfloat stretchZ){
    this->values[10] = stretchZ;
}

GLfloat IAMatrix44_getStretchZForScaleMatrix(IAMatrix44 * this){
    return this->values[10];
}

void IAMatrix44_setRotationZ(IAMatrix44 * this, GLfloat radians){
    this->values[0] = cosf(radians);
    this->values[4] = -sinf(radians);
    this->values[1] = sinf(radians);
    this->values[5] = cosf(radians);
}

void IAMatrix44_setTrimmedRect(IAMatrix44 * this, IARect trimmedRect, IASize originalSize){
    IAMatrix44_setTransformation(this, IARect_make(0.0f, 0.0f, originalSize.width, originalSize.height), trimmedRect);
}

void IAMatrix44_setTransformation(IAMatrix44 * this, IARect oldRect, IARect newRect){
    float stretchX = newRect.size.width / oldRect.size.width;
    float stretchY = newRect.size.height / oldRect.size.height;
    IAMatrix44 scaleMatrix;
    IAMatrix44_makeScaleMatrix(&scaleMatrix, stretchX, stretchY, 1.0f);
    
    float translateX = -0.5f + (newRect.origin.x + newRect.size.width/2.0f) / oldRect.size.width;
    float translateY = -0.5f + (newRect.origin.y + newRect.size.height/2.0f) / oldRect.size.height;
    IAMatrix44 translationMatrix;
    IAMatrix44_makeTranslationMatrix(&translationMatrix, translateX, translateY, 0);
    IAMatrix44_makeWithMultiplikationResult(this, &scaleMatrix, &translationMatrix);
}

void IAMatrix44_setIdentityMatrix(IAMatrix44 * this){
    IAMatrix44_make(this);
    this->values[0] = 1.0f;
    this->values[5] = 1.0f;
    this->values[10] = 1.0f;
    this->values[15] = 1.0f;
}

GLfloat * IAMatrix44_getValues(IAMatrix44 * this){
    return this->values;
}

void IAMatrix44_setValuesFromMatrix(IAMatrix44 * this, IAMatrix44 * matrixWithValuesToCopy){
    if (matrixWithValuesToCopy != NULL) {
        for (int i = 0; i < 16; i++) {
            this->values[i] = matrixWithValuesToCopy->values[i];
        }
    }else{
        for (int i = 0; i < 16; i++) {
            this->values[i] = 0;
        }
    }
}

void IAMatrix44_copySafely(IAMatrix44 * this, IAMatrix44 ** destination){
    if (this != NULL) {
        *destination = IAMatrix44_newCopy(this);
    }else{
        *destination = NULL;
    }
}

void IAMatrix44_releaseMatrixIfNotNull(IAMatrix44 * this){
    if (this != NULL) {
        IAMatrix44_release(this);
    }
}


