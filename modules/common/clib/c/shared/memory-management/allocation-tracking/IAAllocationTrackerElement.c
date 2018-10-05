#include "IALibrary.h"
#include "IAAllocationTrackerElement.h"

#define CLASSNAME "IAAllocationTrackerElement"

#ifdef DEBUG

void IAAllocationTrackerElement_make(IAAllocationTrackerElement * this){
    *this = (IAAllocationTrackerElement){
        .base = IAObject_make(this),
        .allocationCount = 0,
        .positiveAllocationSize = 0,
        .negativeAllocationSize = 0
    };
}

void IAAllocationTrackerElement_incrementAllocationCount(IAAllocationTrackerElement * this){
    this->allocationCount++;
}

void IAAllocationTrackerElement_decrementAllocationCount(IAAllocationTrackerElement * this){
    this->allocationCount--;
}

static void IAAllocationTrackerElement_reduceAllocationSize(IAAllocationTrackerElement * this){
    size_t min = this->positiveAllocationSize > this->negativeAllocationSize ? this->negativeAllocationSize : this->positiveAllocationSize;
    this->positiveAllocationSize -= min;
    this->negativeAllocationSize -= min;
}

void IAAllocationTrackerElement_onAllocated(IAAllocationTrackerElement * this, size_t allocatedSize){
    this->allocationCount++;
    this->positiveAllocationSize += allocatedSize;
    IAAllocationTrackerElement_reduceAllocationSize(this);
}

void IAAllocationTrackerElement_onReallocated(IAAllocationTrackerElement * this, size_t allocatedSize, size_t deallocatedSize){
    this->positiveAllocationSize += allocatedSize;
    this->negativeAllocationSize += deallocatedSize;
    IAAllocationTrackerElement_reduceAllocationSize(this);
}

void IAAllocationTrackerElement_onDeallocated(IAAllocationTrackerElement * this, size_t deallocatedSize){
    this->allocationCount--;
    this->negativeAllocationSize += deallocatedSize;
    IAAllocationTrackerElement_reduceAllocationSize(this);
}

#endif

