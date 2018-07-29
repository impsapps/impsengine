//
//  IAAllocationTrackingElement.h
//  CLib
//
//  Created by Konstantin Merker on 27.05.18.
//Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAllocationTrackingElement_h
#define IAAllocationTrackingElement_h

#ifdef DEBUG

#include "IAObject.h"

typedef struct{
    //@extend
    IAObject base;
    //@set+get
    size_t size;
    //@getAsConst
    char * className;
    //@get
    bool isObject;
} IAAllocationTrackingElement;


void IAAllocationTrackingElement_init(IAAllocationTrackingElement *, size_t size, const char * className, bool isObject);

void IAAllocationTrackingElement_deinit(IAAllocationTrackingElement *);

#include "IAAllocationTrackingElement+Generated.h"

#endif

#endif
