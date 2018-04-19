//
//  IAHashMapIterator.h
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 31.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#ifndef ImpsEngineCLibrary_IAHashMapIterator_h
#define ImpsEngineCLibrary_IAHashMapIterator_h

#include "IAHashMap.h"

typedef struct{
    const IAHashMap * hashMap;
    size_t listIndex;
    IAHashMapList * currentListElement;
    void * (*returnResult)(IAHashMapList*);
} IAHashMapIterator;

void IAHashMapIterator_makeIteratorOverValues(IAHashMapIterator *, const IAHashMap * hashMap);
void IAHashMapIterator_makeIteratorOverKeys(IAHashMapIterator *, const IAHashMap * hashMap);

void * IAHashMapIterator_getNextObject(IAHashMapIterator *);

#include "IAHashMapIterator+Generated.h"

#define hashMapKeys(...) keys(IAHashMap, __VA_ARGS__)
#define hashMapValues(...) values(IAHashMap, __VA_ARGS__)

#endif
