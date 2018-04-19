//
//  IAArrayListIterator.h
//  CLib
//
//  Created by Konstantin Merker on 30/11/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAArrayListIterator_h
#define IAArrayListIterator_h

#include "IAArrayList.h"

typedef struct{
    const IAArrayList * arrayList;
    size_t numberOfElementsLeft;
    size_t indexOfCurrentElement;
} IAArrayListIterator;


void IAArrayListIterator_make(IAArrayListIterator *, const IAArrayList * arrayList);

void * IAArrayListIterator_getNextObject(IAArrayListIterator *);

#include "IAArrayListIterator+Generated.h"

#define arrayList(...) list(IAArrayList, __VA_ARGS__)

#endif
