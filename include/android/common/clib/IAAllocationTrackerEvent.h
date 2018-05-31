//  
//  This file has been automatically generated.
//  
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//  

#ifndef IAAllocationTrackerEvent_h
#define IAAllocationTrackerEvent_h

#include "IAArrayList.h"
#include "IAArrayListIterator.h"
#include "IALibrary.h"

typedef struct{
	IAArrayList delegates;
} IAAllocationTrackerEvent;

IA_CONSTRUCTOR static inline void IAAllocationTrackerEvent_init(IAAllocationTrackerEvent * this){
	IAArrayList_init(&this->delegates, 8);
	IA_increaseAllocationCountForClass("IAAllocationTrackerEvent");
}

IA_CONSTRUCTOR static inline IAAllocationTrackerEvent * IAAllocationTrackerEvent_new(){
	IAAllocationTrackerEvent * this = IA_mallocWithClassName(sizeof(IAAllocationTrackerEvent), "IAAllocationTrackerEvent");
	IAAllocationTrackerEvent_init(this);
	return this;
}

/// \memberof IAAllocationTrackerDelegate
static inline void IAAllocationTrackerEvent_register(IAAllocationTrackerEvent * this, IAAllocationTrackerDelegate * delegate){
	IAArrayList_add(&this->delegates, delegate);
}

/// \memberof IAAllocationTrackerDelegate
static inline IAAllocationTrackerDelegate * IAAllocationTrackerEvent_unregister(IAAllocationTrackerEvent * this, IAAllocationTrackerDelegate * delegate){
	return IAArrayList_removeObject(&this->delegates, delegate);
}

/// \memberof IAAllocationTrackerDelegate
static inline void IAAllocationTrackerEvent_onObjectAllocated(const IAAllocationTrackerEvent * this, const void * allocatedObject, size_t size, const char * className){
	IAAllocationTrackerDelegate * delegate;
	foreach (delegate in arrayList(&this->delegates)) {
		IAAllocationTrackerDelegate_onObjectAllocated(delegate, allocatedObject, size, className);
	}
}

/// \memberof IAAllocationTrackerDelegate
static inline void IAAllocationTrackerEvent_onObjectReallocated(const IAAllocationTrackerEvent * this, const void * allocatedObject, size_t oldSize, size_t newSize, const char * className){
	IAAllocationTrackerDelegate * delegate;
	foreach (delegate in arrayList(&this->delegates)) {
		IAAllocationTrackerDelegate_onObjectReallocated(delegate, allocatedObject, oldSize, newSize, className);
	}
}

/// \memberof IAAllocationTrackerDelegate
static inline void IAAllocationTrackerEvent_onObjectDeallocated(const IAAllocationTrackerEvent * this, const void * deallocatedObject, size_t allocationSize, const char * className){
	IAAllocationTrackerDelegate * delegate;
	foreach (delegate in arrayList(&this->delegates)) {
		IAAllocationTrackerDelegate_onObjectDeallocated(delegate, deallocatedObject, allocationSize, className);
	}
}

IA_DESTRUCTOR static inline void IAAllocationTrackerEvent_deinit(IAAllocationTrackerEvent * this){
	IAArrayList_deinit(&this->delegates);
	IA_decreaseAllocationCountForClass("IAAllocationTrackerEvent");
}

IA_DESTRUCTOR static inline void IAAllocationTrackerEvent_release(IAAllocationTrackerEvent * this){
	IAAllocationTrackerEvent_deinit(this);
	IA_freeWithClassName(this, "IAAllocationTrackerEvent");
}


#endif

