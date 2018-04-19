//
//  IAHashMap.h
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 25.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineCLibrary_IAHashMap_h
#define ImpsEngineCLibrary_IAHashMap_h

#include "IAString.h"


typedef struct IAHashMapList IAHashMapList;

struct IAHashMapList{
    void * object;
    IAHashMapList * next;
    char key[];
};

typedef struct{
    //@get
    size_t size;
    IAHashMapList ** list;
} IAHashMap;


void IAHashMap_init(IAHashMap *, size_t estimatedNumberOfElements);
void IAHashMap_initWithFixedSize(IAHashMap *, size_t fixedSize);

void IAHashMap_add(IAHashMap *, const char * key, void * object);

bool IAHashMap_containsKey(const IAHashMap *, const char * key);
void * IAHashMap_get(const IAHashMap *, const char * key);

void * IAHashMap_remove(IAHashMap *, const char *  key);

void IAHashMap_clear(IAHashMap *);

void IAHashMap_changeSize(IAHashMap *, size_t estimatedNumberOfElements);
void IAHashMap_changeSizeWithFixedSize(IAHashMap *, size_t fixedSize);

void IAHashMap_callFunctionOnAllObjects(const IAHashMap *, void(*function)(void * object));

void IAHashMap_deinit(IAHashMap *);

#include "IAHashMapIterator.h"
#include "IAHashMap+Generated.h"

#endif


