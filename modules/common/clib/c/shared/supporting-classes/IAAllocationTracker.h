//
//  IAAllocationTracker.h
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 25.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAllocationTracker_h
#define IAAllocationTracker_h

#include <stdbool.h>

#ifdef DEBUG

#include <pthread.h>

#define IA_TRACKING_CONTEXT_0 700
#define IA_TRACKING_CONTEXT_1 701
#define IA_TRACKING_CONTEXT_2 702
#define IA_TRACKING_CONTEXT_3 703
#define IA_TRACKING_CONTEXT_4 704
#define IA_TRACKING_CONTEXT_5 705
#define IA_TRACKING_CONTEXT_6 706
#define IA_TRACKING_CONTEXT_7 707

#define IA_TRACKING_CONTEXT_DEFAULT IA_TRACKING_CONTEXT_0


void IAAllocationTracker_commence(void);

int IAAllocationTracker_getContext(void);
void IAAllocationTracker_setContext(int trackingContext);

void IAAllocationTracker_objectAllocated(const char * className);
void IAAllocationTracker_objectDeallocated(const char * className);

int IAAllocationTracker_getCurrentAllocationCountForObject(const char * className);
bool IAAllocationTracker_areObjectsAllocated(void);

void IAAllocationTracker_log(void);
void IAAllocationTracker_assert(void);

void IAAllocationTracker_terminate(void);

#define IA_increaseAllocationCount() do { IAAllocationTracker_objectAllocated(CLASSNAME); } while(0)
#define IA_increaseAllocationCountForClass(className) do { IAAllocationTracker_objectAllocated(className); } while(0)
#define IA_decreaseAllocationCount() do { IAAllocationTracker_objectDeallocated(CLASSNAME); } while(0)
#define IA_decreaseAllocationCountForClass(className) do { IAAllocationTracker_objectDeallocated(className); } while(0)

#else

#define IA_increaseAllocationCount()
#define IA_increaseAllocationCountForClass(className)
#define IA_decreaseAllocationCount()
#define IA_decreaseAllocationCountForClass(className)

#endif

#endif
