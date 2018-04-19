//
//  IAArrayBuffer.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 18.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAArrayBuffer.h"

#define CLASSNAME "IAArrayBuffer"


void IAArrayBuffer_init(IAArrayBuffer * this, size_t size, GLvoid * data, GLenum usage){
	IABuffer_init((IABuffer *) this, GL_ARRAY_BUFFER, size, data, usage);
}

void IAArrayBuffer_initCopy(IAArrayBuffer * this, const IAArrayBuffer * bufferToCopy){
    IABuffer_initCopy((IABuffer *) this, (const IABuffer *) bufferToCopy);
}

void IAArrayBuffer_deinit(IAArrayBuffer * this){
    IABuffer_deinit((IABuffer *) this);
}


