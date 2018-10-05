#ifndef IAAllocationTrackerElement_h
#define IAAllocationTrackerElement_h

#ifdef DEBUG

#include "IAObject.h"

typedef struct{
    //@extend
    IAObject base;
    //@get
    long allocationCount;
    //@get
    size_t positiveAllocationSize;
    //@get
    size_t negativeAllocationSize;
} IAAllocationTrackerElement;


void IAAllocationTrackerElement_make(IAAllocationTrackerElement * this);

void IAAllocationTrackerElement_incrementAllocationCount(IAAllocationTrackerElement * this);
void IAAllocationTrackerElement_decrementAllocationCount(IAAllocationTrackerElement * this);

void IAAllocationTrackerElement_onAllocated(IAAllocationTrackerElement * this, size_t allocatedSize);
void IAAllocationTrackerElement_onReallocated(IAAllocationTrackerElement * this, size_t allocatedSize, size_t deallocatedSize);
void IAAllocationTrackerElement_onDeallocated(IAAllocationTrackerElement * this, size_t deallocatedSize);

#include "IAAllocationTrackerElement+Generated.h"

#endif

#endif
