//
//  IAAutoExpandingHashMapIterator.h
//  Hit Verto
//
//  Created by Konstantin Merker on 12/10/15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAAutoExpandingHashMapIterator_h
#define Hit_Verto_IAAutoExpandingHashMapIterator_h

#include "IAAutoExpandingHashMap.h"
#include "IAHashMapIterator.h"

typedef struct{
    //@extend
    IAHashMapIterator iterator;
} IAAutoExpandingHashMapIterator;

void IAAutoExpandingHashMapIterator_makeIteratorOverValues(IAAutoExpandingHashMapIterator *, const IAAutoExpandingHashMap * hashMap);
void IAAutoExpandingHashMapIterator_makeIteratorOverKeys(IAAutoExpandingHashMapIterator *, const IAAutoExpandingHashMap * hashMap);

#define autoExpandingHashMapKeys(...) keys(IAAutoExpandingHashMap, __VA_ARGS__)
#define autoExpandingHashMapValues(...) values(IAAutoExpandingHashMap, __VA_ARGS__)

#include "IAAutoExpandingHashMapIterator+Generated.h"

#endif
