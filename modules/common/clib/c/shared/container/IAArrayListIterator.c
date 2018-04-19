//
//  IAArrayListIterator.c
//  CLib
//
//  Created by Konstantin Merker on 30/11/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAArrayListIterator.h"

#define CLASSNAME "IAArrayListIterator"


void IAArrayListIterator_make(IAArrayListIterator * this, const IAArrayList * arrayList){
    this->arrayList = arrayList;
    this->numberOfElementsLeft = IAArrayList_getCurrentSize(arrayList);
    this->indexOfCurrentElement = arrayList->offset;
}

void * IAArrayListIterator_getNextObject(IAArrayListIterator * this){
    if (this->numberOfElementsLeft == 0) {
        return NULL;
    }
    void * object = this->arrayList->objects[this->indexOfCurrentElement];
    this->indexOfCurrentElement++;
    if (this->indexOfCurrentElement == IAArrayList_getArraySize(this->arrayList)) {
        this->indexOfCurrentElement = 0;
    }
    this->numberOfElementsLeft--;
    return object;
}

