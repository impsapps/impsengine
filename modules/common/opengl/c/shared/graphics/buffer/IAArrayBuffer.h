//
//  IAArrayBuffer.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 18.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#ifndef ImpsEngineiOS_IAArrayBuffer_h
#define ImpsEngineiOS_IAArrayBuffer_h

#include "IAOpenGLHeaders.h"
#include "IABuffer.h"
#include "IAOpenGLResourceDelegate.h"

typedef struct{
    //@extend
    IABuffer buffer;
} IAArrayBuffer;


void IAArrayBuffer_init(IAArrayBuffer *, size_t size, GLvoid * data, GLenum usage);
void IAArrayBuffer_initCopy(IAArrayBuffer *, const IAArrayBuffer * bufferToCopy);

void IAArrayBuffer_deinit(IAArrayBuffer *);

#include "IAArrayBuffer+Generated.h"

#endif
