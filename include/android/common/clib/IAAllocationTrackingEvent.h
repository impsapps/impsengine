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
#include "IAAllocationTrackingDelegate.h"

typedef struct{
	IAArrayList delegates;
} IAAllocationTrackingEvent;

IA_CONSTRUCTOR static inline void IAAllocationTrackingEvent_init(IAAllocationTrackingEvent * this){
	IAArrayList_init(&this->delegates, 8);
	IA_incrementInitCountForClass("IAAllocationTrackingEvent");
}

static inline void IAAllocationTrackingEvent_deinit(IAAllocationTrackingEvent * this);
IA_CONSTRUCTOR static inline IAAllocationTrackingEvent * IAAllocationTrackingEvent_new(){
	IAAllocationTrackingEvent * this = IA_internal_newWithClassName(sizeof(IAAllocationTrackingEvent), (void (*)(void *)) IAAllocationTrackingEvent_deinit, "IAAllocationTrackingEvent");
	IAAllocationTrackingEvent_init(this);
	return this;
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_retain(IAAllocationTrackingEvent * this){
	IA_retain(this);
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
static inline void IAAllocationTrackingEvent_onObjectAllocated(const IAAllocationTrackingEvent * this, const void * objectPointer, size_t allocationSize, const char * className){
	IAAllocationTrackingDelegate * delegate;
	foreach (delegate in arrayList(&this->delegates)) {
		IAAllocationTrackingDelegate_onObjectAllocated(delegate, objectPointer, allocationSize, className);
	}
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_onObjectDeallocated(const IAAllocationTrackingEvent * this, const void * objectPointer, size_t allocationSize, const char * className){
	IAAllocationTrackingDelegate * delegate;
	foreach (delegate in arrayList(&this->delegates)) {
		IAAllocationTrackingDelegate_onObjectDeallocated(delegate, objectPointer, allocationSize, className);
	}
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_onDataAllocated(const IAAllocationTrackingEvent * this, const void * dataPointer, size_t size, const char * className){
	IAAllocationTrackingDelegate * delegate;
	foreach (delegate in arrayList(&this->delegates)) {
		IAAllocationTrackingDelegate_onDataAllocated(delegate, dataPointer, size, className);
	}
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_onDataReallocated(const IAAllocationTrackingEvent * this, const void * oldDataPointer, const void * newDataPointer, size_t newSize, size_t oldSize, const char * className){
	IAAllocationTrackingDelegate * delegate;
	foreach (delegate in arrayList(&this->delegates)) {
		IAAllocationTrackingDelegate_onDataReallocated(delegate, oldDataPointer, newDataPointer, newSize, oldSize, className);
	}
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_onDataDeallocated(const IAAllocationTrackingEvent * this, const void * dataPointer, size_t size, const char * className){
	IAAllocationTrackingDelegate * delegate;
	foreach (delegate in arrayList(&this->delegates)) {
		IAAllocationTrackingDelegate_onDataDeallocated(delegate, dataPointer, size, className);
	}
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_onInitCountIncremented(const IAAllocationTrackingEvent * this, const char * className){
	IAAllocationTrackingDelegate * delegate;
	foreach (delegate in arrayList(&this->delegates)) {
		IAAllocationTrackingDelegate_onInitCountIncremented(delegate, className);
	}
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_onInitCountDecremented(const IAAllocationTrackingEvent * this, const char * className){
	IAAllocationTrackingDelegate * delegate;
	foreach (delegate in arrayList(&this->delegates)) {
		IAAllocationTrackingDelegate_onInitCountDecremented(delegate, className);
	}
}

static inline void IAAllocationTrackingEvent_deinit(IAAllocationTrackingEvent * this){
	IAArrayList_deinit(&this->delegates);
	IA_decrementInitCountForClass("IAAllocationTrackingEvent");
}

static inline void IAAllocationTrackingEvent_release(IAAllocationTrackingEvent * this){
	IA_release(this);
}


#endif

