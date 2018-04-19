//
//  IAAutoExpandingHashMap.h
//  Hit Verto
//
//  Created by Konstantin Merker on 12/10/15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAAutoExpandingHashMap_h
#define Hit_Verto_IAAutoExpandingHashMap_h

#include "IAHashMap.h"

typedef struct{
    //@get
    IAHashMap * currentHashMap;
    size_t currentNumberOfObjects;
} IAAutoExpandingHashMap;

void IAAutoExpandingHashMap_init(IAAutoExpandingHashMap *);

void IAAutoExpandingHashMap_add(IAAutoExpandingHashMap *, const char * key, void * object);

bool IAAutoExpandingHashMap_containsKey(const IAAutoExpandingHashMap *, const char * key);
void * IAAutoExpandingHashMap_get(const IAAutoExpandingHashMap *, const char * key);
size_t IAAutoExpandingHashMap_getCurrentNumberOfObjects(const IAAutoExpandingHashMap *);

void * IAAutoExpandingHashMap_remove(IAAutoExpandingHashMap *, const char *  key);

void IAAutoExpandingHashMap_clear(IAAutoExpandingHashMap *);

void IAAutoExpandingHashMap_callFunctionOnAllObjects(const IAAutoExpandingHashMap *, void(*function)(void * object));

void IAAutoExpandingHashMap_deinit(IAAutoExpandingHashMap *);

#include "IAAutoExpandingHashMapIterator.h"
#include "IAAutoExpandingHashMap+Generated.h"

#endif
