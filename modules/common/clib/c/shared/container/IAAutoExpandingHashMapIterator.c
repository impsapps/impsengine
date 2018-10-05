#include "IALibrary.h"
#include "IAAutoExpandingHashMapIterator.h"

#define CLASSNAME "IAAutoExpandingHashMapIterator"


void IAAutoExpandingHashMapIterator_makeIteratorOverValues(IAAutoExpandingHashMapIterator * this, const IAAutoExpandingHashMap * hashMap){
    IAHashMapIterator_makeIteratorOverValues((IAHashMapIterator *) this, hashMap->currentHashMap);
}

void IAAutoExpandingHashMapIterator_makeIteratorOverKeys(IAAutoExpandingHashMapIterator * this, const IAAutoExpandingHashMap * hashMap){
    IAHashMapIterator_makeIteratorOverKeys((IAHashMapIterator *) this, hashMap->currentHashMap);
}


