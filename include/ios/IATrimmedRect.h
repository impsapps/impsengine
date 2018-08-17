//
//  IATrimmedRect.h
//  OpenGL
//
//  Created by Konstantin Merker on 27/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IATrimmedRect_h
#define IATrimmedRect_h

#include "IARect.h"

typedef struct{
    IASize baseSize;
    IARect trimmedRect;
} IATrimmedRect;


void IATrimmedRect_make(IATrimmedRect *, IASize baseSize, IARect trimmedRect);
void IATrimmedRect_makeCopy(IATrimmedRect *, const IATrimmedRect * trimmedRectToCopy);

void IATrimmedRect_flipHorizontally(IATrimmedRect *);
void IATrimmedRect_flipVertically(IATrimmedRect *);

IARect IATrimmedRect_trimRect(const IATrimmedRect *, IARect rect);

#include "IATrimmedRect+Generated.h"

#endif
