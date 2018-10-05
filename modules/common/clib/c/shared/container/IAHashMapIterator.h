#ifndef IAHashMapIterator_h
#define IAHashMapIterator_h

#include "IAHashMap.h"

typedef struct{
    //@extend
    IAObject base;
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
