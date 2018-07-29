//
//  IAStructMemoryHandler.h
//  CLib
//
//  Created by Konstantin Merker on 30/01/17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAStructMemoryHandler_h
#define IAStructMemoryHandler_h

#include "IAArrayList.h"

typedef struct{
    //@extend
    IAObject base;
    size_t sizeOfStruct;
    size_t numberOfStructsAllocatedAtOnce;
    size_t currentElementInStructArray;
    size_t currentStructArrayIndex;
    IAArrayList pointersToStructArrays;
    IAArrayList pointersToRecycledStructs;
} IAStructMemoryHandler;


void IAStructMemoryHandler_init(IAStructMemoryHandler *, size_t sizeOfStruct, size_t numberOfStructsAllocatedAtOnce);

void * IAStructMemoryHandler_getPointerToNextStruct(IAStructMemoryHandler *);

/**
 *     Only call this method with pointers received by calling the function "IAStructMemoryHandler_getPointerToNextStruct(IAStructMemoryHandler *)".
 *     Struct memory handler will use passed pointers to return them again, if asked for another pointer to a struct.
 */
void IAStructMemoryHandler_recyclePointerToStruct(IAStructMemoryHandler *, void * pointer);

void IAStructMemoryHandler_reset(IAStructMemoryHandler *);

void IAStructMemoryHandler_deinit(IAStructMemoryHandler *);

#include "IAStructMemoryHandler+Generated.h"

#endif
