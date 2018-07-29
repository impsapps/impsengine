//
//  IAArrayIterator.h
//  CLib
//
//  Created by Konstantin Merker on 12/11/17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAArrayIterator_h
#define IAArrayIterator_h

#include "IAArray.h"

typedef struct{
    //@extend
    IAObject base;
    const IAArray * array;
    size_t indexForNextObject;
} IAArrayIterator;


void IAArrayIterator_make(IAArrayIterator *, const IAArray * array);

void * IAArrayIterator_getNextObject(IAArrayIterator *);

#include "IAArrayIterator+Generated.h"

#define array(...) list(IAArray, __VA_ARGS__)

#endif
