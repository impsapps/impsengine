//
//  IAArrayIterator.c
//  CLib
//
//  Created by Konstantin Merker on 12/11/17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAArrayIterator.h"

#define CLASSNAME "IAArrayIterator"


void IAArrayIterator_make(IAArrayIterator * this, const IAArray * array){
    *this = (IAArrayIterator){
        .base = IAObject_make(this),
        .array = array,
        .indexForNextObject = 0
    };
}

void * IAArrayIterator_getNextObject(IAArrayIterator * this){
    while (this->indexForNextObject < IAArray_getSize(this->array)) {
        void * object = IAArray_get(this->array, this->indexForNextObject);
        this->indexForNextObject++;
        if (object != NULL) {
            return object;
        }
    }
    return NULL;
}

