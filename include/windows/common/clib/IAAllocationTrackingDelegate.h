//
//  IAAllocationTrackingDelegate.h
//  CLib
//
//  Created by Konstantin Merker on 27.05.18.
//Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAllocationTrackingDelegate_h
#define IAAllocationTrackingDelegate_h

#ifdef DEBUG

#include <stdint.h>

//@event
typedef struct{
    void * correspondingObject;
    //@exe
    void (*onObjectAllocated)(void * correspondingObject, const void * allocatedObject, size_t size, const char * className);
    //@exe
    void (*onObjectReallocated)(void * correspondingObject, const void * allocatedObject, size_t oldSize, size_t newSize, const char * className);
    //@exe
    void (*onObjectDeallocated)(void * correspondingObject, const void * deallocatedObject, size_t allocationSize, const char * className);
} IAAllocationTrackingDelegate;

#include "IAAllocationTrackingDelegate+Generated.h"

#endif
#endif
