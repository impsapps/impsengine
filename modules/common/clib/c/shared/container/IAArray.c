//
//  IAArray.c
//  Hit Verto
//
//  Created by Konstantin Merker on 23/03/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAArray.h"
#include <stdarg.h>
#include <string.h>

#define CLASSNAME "IAArray"

static void IAArray_setObjectsWithVaribleArguments(IAArray * this, va_list args);


void IAArray_init(IAArray * this, size_t size){
    this->base = IAObject_make(this);
    this->objects = IA_calloc(size, sizeof(void *));
    this->size = size;
    IA_incrementInitCount();
}

void IAArray_initWithObjects(IAArray * this, size_t size, ...){
    IAArray_init(this, size);
    va_list args;
    va_start(args, size);
    IAArray_setObjectsWithVaribleArguments(this, args);
    va_end(args);
}

IAArray * IAArray_newWithObjects(size_t size, ...){
    IAArray * this = IAArray_new(size);
    va_list args;
    va_start(args, size);
    IAArray_setObjectsWithVaribleArguments(this, args);
    va_end(args);
    return this;
}

IAArray * IAArray_withObjects(size_t size, ...){
    IAArray * this = IAArray_with(size);
    va_list args;
    va_start(args, size);
    IAArray_setObjectsWithVaribleArguments(this, args);
    va_end(args);
    return this;
}

static void IAArray_setObjectsWithVaribleArguments(IAArray * this, va_list args){
    for (size_t i = 0; i < this->size; i++) {
        void * object = va_arg(args, void *);
        if (object) {
            IA_retain(object);
        }
        this->objects[i] = object;
    }
}

void IAArray_set(IAArray * this, size_t index, void * object){
    IA_retain(object);
    if (this->objects[index] != NULL) {
        IA_autorelease(this->objects[index]);
    }
    this->objects[index] = object;
}

void * IAArray_get(const IAArray * this, size_t index){
    return this->objects[index];
}

void IAArray_callFunctionOnAllObjects(const IAArray * this, void(*function)(void * object)){
    void * object;
    foreach (object in array(this)){
        function(object);
    }
}

void IAArray_deinit(IAArray * this){
    void * object;
    foreach (object in array(this)){
        IA_release(object);
    }
    IA_free(this->objects);
    IA_decrementInitCount();
}


