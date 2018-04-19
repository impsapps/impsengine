//
//  IAStructMemoryHandler.c
//  CLib
//
//  Created by Konstantin Merker on 30/01/17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAStructMemoryHandler.h"

#define CLASSNAME "IAStructMemoryHandler"


void * IAStructMemoryHandler_getCurrentStructArray(IAStructMemoryHandler * this);
void IAStructMemoryHandler_addStructArray(IAStructMemoryHandler * this);
void IAStructMemoryHandler_destroyStructArray(void * structArray);


void IAStructMemoryHandler_init(IAStructMemoryHandler * this, size_t sizeOfStruct, size_t numberOfStructsAllocatedAtOnce){
    this->sizeOfStruct = sizeOfStruct;
    this->numberOfStructsAllocatedAtOnce = numberOfStructsAllocatedAtOnce;
    this->currentElementInStructArray = 0;
    this->currentStructArrayIndex = 0;
    IAArrayList_init(&this->pointersToStructArrays, 10);
    IAArrayList_init(&this->pointersToRecycledStructs, 10);
    IA_increaseAllocationCount();
}

void * IAStructMemoryHandler_getPointerToNextStruct(IAStructMemoryHandler * this){
    if (IAArrayList_isEmpty(&this->pointersToRecycledStructs) == false) {
        return IAArrayList_removeAtIndex(&this->pointersToRecycledStructs, 0);
    }
    char * structArray = IAStructMemoryHandler_getCurrentStructArray(this);
    structArray += this->currentElementInStructArray * this->sizeOfStruct;
    this->currentElementInStructArray++;
    if (this->currentElementInStructArray == this->numberOfStructsAllocatedAtOnce) {
        this->currentElementInStructArray = 0;
        this->currentStructArrayIndex++;
    }
    return structArray;
}

void IAStructMemoryHandler_recyclePointerToStruct(IAStructMemoryHandler * this, void * pointer){
    IAArrayList_add(&this->pointersToRecycledStructs, pointer);
}

void IAStructMemoryHandler_reset(IAStructMemoryHandler * this){
    this->currentElementInStructArray = 0;
    this->currentStructArrayIndex = 0;
    IAArrayList_clear(&this->pointersToRecycledStructs);
}

void * IAStructMemoryHandler_getCurrentStructArray(IAStructMemoryHandler * this){
    debugAssert(this->currentStructArrayIndex <= IAArrayList_getCurrentSize(&this->pointersToStructArrays));
    if (this->currentStructArrayIndex == IAArrayList_getCurrentSize(&this->pointersToStructArrays)) {
        IAStructMemoryHandler_addStructArray(this);
    }
    return IAArrayList_get(&this->pointersToStructArrays, this->currentStructArrayIndex);
}

void IAStructMemoryHandler_addStructArray(IAStructMemoryHandler * this){
    void * structArray = IA_malloc(this->sizeOfStruct * this->numberOfStructsAllocatedAtOnce);
    IAArrayList_add(&this->pointersToStructArrays, structArray);
}

void IAStructMemoryHandler_destroyStructArray(void * structArray){
    IA_free(structArray);
}

void IAStructMemoryHandler_deinit(IAStructMemoryHandler * this){
    IAArrayList_callFunctionOnAllObjects(&this->pointersToStructArrays, IAStructMemoryHandler_destroyStructArray);
    IAArrayList_deinit(&this->pointersToStructArrays);
    IAArrayList_deinit(&this->pointersToRecycledStructs);
    IA_decreaseAllocationCount();
}
