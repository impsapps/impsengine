//
//  IAAllocationTracker+Internal.h
//  CLib
//
//  Created by Konstantin Merker on 27.05.18.
//  Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAllocationTracker_Internal_h
#define IAAllocationTracker_Internal_h

#ifdef DEBUG

void IAAllocationTracker_objectAllocated(const void * object, size_t size, const char * className);
void IAAllocationTracker_objectReallocated(const void * object, size_t newSize);
void IAAllocationTracker_objectDeallocated(const void * object);

void IAAllocationTracker_increaseAllocationCount(const char * className);
void IAAllocationTracker_decreaseAllocationCount(const char * className);

#endif

#endif
