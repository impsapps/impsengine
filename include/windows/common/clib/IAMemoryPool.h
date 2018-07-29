//
//  IAMemoryPool.h
//  CLib
//
//  Created by Konstantin Merker on 15.07.18.
//Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAMemoryPool_h
#define IAMemoryPool_h

#include "IAObject.h"
#include "IAStructArrayList.h"
#include "IAMemoryPoolElement.h"

IA_STRUCT_ARRAY_LIST(IAMemoryPoolElement)

typedef struct{
    //@extend
    IAObject base;
    IAStructArrayList_IAMemoryPoolElement * elements;
    long shouldReleaseImmediatlyCount;
} IAMemoryPool;


void IAMemoryPool_init(IAMemoryPool * this);

void IAMemoryPool_incrementShouldReleaseImmediatlyCount(IAMemoryPool * this);
void IAMemoryPool_decrementShouldReleaseImmediatlyCount(IAMemoryPool * this);

void IAMemoryPool_add(IAMemoryPool * this, void * object);
void IAMemoryPool_run(IAMemoryPool * this);

void IAMemoryPool_deinit(IAMemoryPool * this);

#include "IAMemoryPool+Generated.h"

#endif
