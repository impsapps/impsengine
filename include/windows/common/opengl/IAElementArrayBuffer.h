//
//  IAElementArrayBuffer.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 18.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#ifndef ImpsEngineiOS_IAElementArrayBuffer_h
#define ImpsEngineiOS_IAElementArrayBuffer_h

#include "IAOpenGLHeaders.h"
#include "IABuffer.h"

typedef struct{
    //@extend
    IABuffer buffer;
} IAElementArrayBuffer;


void IAElementArrayBuffer_init(IAElementArrayBuffer *, size_t size, GLvoid * data, GLenum usage);
void IAElementArrayBuffer_initCopy(IAElementArrayBuffer *, const IAElementArrayBuffer * bufferToCopy);

void IAElementArrayBuffer_deinit(IAElementArrayBuffer *);

#include "IAElementArrayBuffer+Generated.h"

#endif
