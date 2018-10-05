#ifndef IAAutoExpandingHashMapIterator_h
#define IAAutoExpandingHashMapIterator_h

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
