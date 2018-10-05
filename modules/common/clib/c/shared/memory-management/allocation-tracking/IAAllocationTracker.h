#ifndef IAAllocationTracker_h
#define IAAllocationTracker_h

#ifdef DEBUG

#include "IAAllocationTrackingDelegate.h"
#include "IAAutoExpandingHashMap.h"

typedef struct{
    //@extend
    IAObject base;
    IAAutoExpandingHashMap * allocatedObjectsPerClass;
    IAAutoExpandingHashMap * allocatedDataPerClass;
    IAAutoExpandingHashMap * initCountPerClass;
    IAAllocationTrackingDelegate trackingDelegate;
} IAAllocationTracker;


void IAAllocationTracker_init(IAAllocationTracker * this);

void IAAllocationTracker_start(IAAllocationTracker * this);
void IAAllocationTracker_stop(IAAllocationTracker * this);

long IAAllocationTracker_getAllocationCountForClass(IAAllocationTracker * this, const char * className);
size_t IAAllocationTracker_getAllocationSizeForClass(IAAllocationTracker * this, const char * className);
bool IAAllocationTracker_isAnythingAllocated(IAAllocationTracker * this);

void IAAllocationTracker_log(IAAllocationTracker * this);
void IAAllocationTracker_assert(IAAllocationTracker * this);

void IAAllocationTracker_deinit(IAAllocationTracker * this);

#include "IAAllocationTracker+Generated.h"

#endif
#endif
