#ifndef IAArrayListIterator_h
#define IAArrayListIterator_h

#include "IAArrayList.h"

typedef struct{
    //@extend
    IAObject base;
    const IAArrayList * arrayList;
    size_t numberOfElementsLeft;
    size_t indexOfCurrentElement;
} IAArrayListIterator;


void IAArrayListIterator_make(IAArrayListIterator *, const IAArrayList * arrayList);

void * IAArrayListIterator_getNextObject(IAArrayListIterator *);

#include "IAArrayListIterator+Generated.h"

#define arrayList(...) list(IAArrayList, __VA_ARGS__)

#endif
