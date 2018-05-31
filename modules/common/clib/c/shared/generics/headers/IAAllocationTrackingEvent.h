//  
//  This file has been automatically generated.
//  
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//  

#ifndef IAAllocationTrackingEvent_h
#define IAAllocationTrackingEvent_h

#include "IAArrayList.h"
#include "IAArrayListIterator.h"
#include "IALibrary.h"

typedef struct{
	IAArrayList delegates;
} IAAllocationTrackingEvent;

IA_CONSTRUCTOR static inline void IAAllocationTrackingEvent_init(IAAllocationTrackingEvent * this){
	IAArrayList_init(&this->delegates, 8);
	IA_increaseAllocationCountForClass("IAAllocationTrackingEvent");
}

IA_CONSTRUCTOR static inline IAAllocationTrackingEvent * IAAllocationTrackingEvent_new(){
	IAAllocationTrackingEvent * this = IA_mallocWithClassName(sizeof(IAAllocationTrackingEvent), "IAAllocationTrackingEvent");
	IAAllocationTrackingEvent_init(this);
	return this;
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_register(IAAllocationTrackingEvent * this, IAAllocationTrackingDelegate * delegate){
	IAArrayList_add(&this->delegates, delegate);
}

/// \memberof IAAllocationTrackingDelegate
static inline IAAllocationTrackingDelegate * IAAllocationTrackingEvent_unregister(IAAllocationTrackingEvent * this, IAAllocationTrackingDelegate * delegate){
	return IAArrayList_removeObject(&this->delegates, delegate);
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_onObjectAllocated(const IAAllocationTrackingEvent * this, const void * allocatedObject, size_t size, const char * className){
	IAAllocationTrackingDelegate * delegate;
	foreach (delegate in arrayList(&this->delegates)) {
		IAAllocationTrackingDelegate_onObjectAllocated(delegate, allocatedObject, size, className);
	}
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_onObjectReallocated(const IAAllocationTrackingEvent * this, const void * allocatedObject, size_t oldSize, size_t newSize, const char * className){
	IAAllocationTrackingDelegate * delegate;
	foreach (delegate in arrayList(&this->delegates)) {
		IAAllocationTrackingDelegate_onObjectReallocated(delegate, allocatedObject, oldSize, newSize, className);
	}
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_onObjectDeallocated(const IAAllocationTrackingEvent * this, const void * deallocatedObject, size_t allocationSize, const char * className){
	IAAllocationTrackingDelegate * delegate;
	foreach (delegate in arrayList(&this->delegates)) {
		IAAllocationTrackingDelegate_onObjectDeallocated(delegate, deallocatedObject, allocationSize, className);
	}
}

IA_DESTRUCTOR static inline void IAAllocationTrackingEvent_deinit(IAAllocationTrackingEvent * this){
	IAArrayList_deinit(&this->delegates);
	IA_decreaseAllocationCountForClass("IAAllocationTrackingEvent");
}

IA_DESTRUCTOR static inline void IAAllocationTrackingEvent_release(IAAllocationTrackingEvent * this){
	IAAllocationTrackingEvent_deinit(this);
	IA_freeWithClassName(this, "IAAllocationTrackingEvent");
}


#endif

