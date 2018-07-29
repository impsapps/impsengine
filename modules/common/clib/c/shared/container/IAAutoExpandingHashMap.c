//
//  IAAutoExpandingHashMap.c
//  Hit Verto
//
//  Created by Konstantin Merker on 12/10/15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAAutoExpandingHashMap.h"

#define CLASSNAME "IAAutoExpandingHashMap"


void IAAutoExpandingHashMap_expand(IAAutoExpandingHashMap * this);

void IAAutoExpandingHashMap_init(IAAutoExpandingHashMap * this){
    this->base = IAObject_make(this);
    this->currentHashMap = IAHashMap_newWithFixedSize(16);
    this->currentNumberOfObjects = 0;
    IA_incrementInitCount();
}

void IAAutoExpandingHashMap_add(IAAutoExpandingHashMap * this, const char * key, void * object){
    debugAssert(this->currentNumberOfObjects / 3 <= IAHashMap_getSize(this->currentHashMap) / 4);
    if (this->currentNumberOfObjects / 3 == IAHashMap_getSize(this->currentHashMap) / 4) {
        IAAutoExpandingHashMap_expand(this);
    }
    IAHashMap_add(this->currentHashMap, key, object);
    this->currentNumberOfObjects++;
}

void IAAutoExpandingHashMap_expand(IAAutoExpandingHashMap * this){
    size_t currentSize = IAHashMap_getSize(this->currentHashMap);
    IAHashMap * newHashMap = IAHashMap_newWithFixedSize(currentSize * 2);
    
    char * key;
    foreach (key in hashMapKeys(this->currentHashMap)) {
        void * object = IAHashMap_get(this->currentHashMap, key);
        IAHashMap_add(newHashMap, key, object);
    }
    
    IAHashMap_release(this->currentHashMap);
    this->currentHashMap = newHashMap;
}

bool IAAutoExpandingHashMap_containsKey(const IAAutoExpandingHashMap * this, const char * key){
    return IAHashMap_containsKey(this->currentHashMap, key);
}

void * IAAutoExpandingHashMap_get(const IAAutoExpandingHashMap * this, const char * key){
    return IAHashMap_get(this->currentHashMap, key);
}

size_t IAAutoExpandingHashMap_getCurrentNumberOfObjects(const IAAutoExpandingHashMap * this){
    return this->currentNumberOfObjects;
}

void * IAAutoExpandingHashMap_remove(IAAutoExpandingHashMap * this, const char *  key){
    void * removedObject = IAHashMap_remove(this->currentHashMap, key);
    if (removedObject) {
        this->currentNumberOfObjects--;
    }
    return removedObject;
}

void IAAutoExpandingHashMap_clear(IAAutoExpandingHashMap * this){
    IAHashMap_clear(this->currentHashMap);
    this->currentNumberOfObjects = 0;
}

void IAAutoExpandingHashMap_callFunctionOnAllObjects(const IAAutoExpandingHashMap * this, void(*function)(void * object)){
    IAHashMap_callFunctionOnAllObjects(this->currentHashMap, function);
}

void IAAutoExpandingHashMap_deinit(IAAutoExpandingHashMap * this){
    IAHashMap_release(this->currentHashMap);
    IA_decrementInitCount();
}


