//
//  IAAllocationTracker.h
//  CLib
//
//  Created by Konstantin Merker on 27.05.18.
//Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAllocationTracker_h
#define IAAllocationTracker_h

#ifdef DEBUG

#include "IAAllocationTrackingDelegate.h"
#include "IAAutoExpandingHashMap.h"

typedef struct{
    IAAutoExpandingHashMap * allocationSizePerClass;
    //@getAsRef
    IAAllocationTrackingDelegate trackingDelegate;
} IAAllocationTracker;


void IAAllocationTracker_init(IAAllocationTracker * this);

long IAAllocationTracker_getAllocationCountForClass(IAAllocationTracker * this, const char * className);
size_t IAAllocationTracker_getAllocationSizeForClass(IAAllocationTracker * this, const char * className);
bool IAAllocationTracker_isAnythingAllocated(IAAllocationTracker * this);

void IAAllocationTracker_log(IAAllocationTracker * this);
void IAAllocationTracker_assert(IAAllocationTracker * this);

void IAAllocationTracker_deinit(IAAllocationTracker * this);

#include "IAAllocationTracker+Generated.h"

#endif
#endif
