//
//  IAAutoExpandingHashMapIterator.c
//  Hit Verto
//
//  Created by Konstantin Merker on 12/10/15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAAutoExpandingHashMapIterator.h"

#define CLASSNAME "IAAutoExpandingHashMapIterator"


void IAAutoExpandingHashMapIterator_makeIteratorOverValues(IAAutoExpandingHashMapIterator * this, const IAAutoExpandingHashMap * hashMap){
    IAHashMapIterator_makeIteratorOverValues((IAHashMapIterator *) this, hashMap->currentHashMap);
}

void IAAutoExpandingHashMapIterator_makeIteratorOverKeys(IAAutoExpandingHashMapIterator * this, const IAAutoExpandingHashMap * hashMap){
    IAHashMapIterator_makeIteratorOverKeys((IAHashMapIterator *) this, hashMap->currentHashMap);
}


