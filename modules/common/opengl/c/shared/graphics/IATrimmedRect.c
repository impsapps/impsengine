//
//  IATrimmedRect.c
//  OpenGL
//
//  Created by Konstantin Merker on 27/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IATrimmedRect.h"

#define CLASSNAME "IATrimmedRect"


void IATrimmedRect_make(IATrimmedRect * this, IASize baseSize, IARect trimmedRect){
    *this = (IATrimmedRect){
        .baseSize = baseSize,
        .trimmedRect = trimmedRect
    };
}

void IATrimmedRect_makeCopy(IATrimmedRect * this, const IATrimmedRect * trimmedRectToCopy){
    *this = *trimmedRectToCopy;
}

static void IATrimmedRect_flipOnAxis(float axisLength, float * p1, float * p2){
    float distanceP1 = *p1;
    float distanceP2 = axisLength - *p2;
    *p1 = distanceP2;
    *p2 = axisLength - distanceP1;
}

void IATrimmedRect_flipHorizontally(IATrimmedRect * this){
    float left = this->trimmedRect.origin.x;
    float top = this->trimmedRect.origin.y;
    float right = left + this->trimmedRect.size.width;
    float bottom = top + this->trimmedRect.size.height;
    IATrimmedRect_flipOnAxis(this->baseSize.width, &left, &right);
    this->trimmedRect = IARect_makeWithLeftTopRightBottom(left, top, right, bottom);
}

void IATrimmedRect_flipVertically(IATrimmedRect * this){
    float left = this->trimmedRect.origin.x;
    float top = this->trimmedRect.origin.y;
    float right = left + this->trimmedRect.size.width;
    float bottom = top + this->trimmedRect.size.height;
    IATrimmedRect_flipOnAxis(this->baseSize.height, &top, &bottom);
    this->trimmedRect = IARect_makeWithLeftTopRightBottom(left, top, right, bottom);
}

IARect IATrimmedRect_trimRect(const IATrimmedRect * this, IARect rect){
    rect.origin.x += rect.size.width / this->baseSize.width * this->trimmedRect.origin.x;
    rect.size.width = rect.size.width / this->baseSize.width * this->trimmedRect.size.width;
    rect.origin.y += rect.size.height / this->baseSize.height * this->trimmedRect.origin.y;
    rect.size.height = rect.size.height / this->baseSize.height * this->trimmedRect.size.height;
    return rect;
}


