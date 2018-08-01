//  
//  This file has been automatically generated.
//  
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//  

#ifndef IAAllocationTrackingEvent_h
#define IAAllocationTrackingEvent_h

#include "IAStructArrayList.h"
#include "IALibrary.h"
#include "IAAllocationTrackingDelegate.h"

typedef struct{
	IAStructArrayList * delegates;
} IAAllocationTrackingEvent;

IA_CONSTRUCTOR static inline void IAAllocationTrackingEvent_init(IAAllocationTrackingEvent * this){
	IA_STRUCT_ARRAY_LIST_VOID_MALLOC_MAKE_WITH_CLASSNAME(this->delegates, 8, "IAAllocationTrackingEvent");
	IA_incrementInitCountForClass("IAAllocationTrackingEvent");
}

static inline void IAAllocationTrackingEvent_deinit(IAAllocationTrackingEvent * this);
IA_CONSTRUCTOR static inline IAAllocationTrackingEvent * IAAllocationTrackingEvent_new(){
	IAAllocationTrackingEvent * this = IA_newWithClassName(sizeof(IAAllocationTrackingEvent), (void (*)(void *)) IAAllocationTrackingEvent_deinit, "IAAllocationTrackingEvent");
	IAAllocationTrackingEvent_init(this);
	return this;
}

static inline IAAllocationTrackingEvent * IAAllocationTrackingEvent_with(){
	IAAllocationTrackingEvent * this = IAAllocationTrackingEvent_new();
	IA_autorelease(this);
	return this;
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_retain(IAAllocationTrackingEvent * this){
	IA_retain(this);
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_register(IAAllocationTrackingEvent * this, IAAllocationTrackingDelegate * delegate){
	IA_retain(delegate);
	IA_STRUCT_ARRAY_LIST_VOID_REALLOC_MAKE_IF_NEEDED_WITH_CLASSNAME(this->delegates, "IAAllocationTrackingEvent");
	IAStructArrayList_add(this->delegates, delegate);
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_unregister(IAAllocationTrackingEvent * this, IAAllocationTrackingDelegate * delegate){
	debugOnly(bool isFound = false;)
	for (size_t i = 0; i < IAStructArrayList_getCurrentSize(this->delegates); i++) {
		IAAllocationTrackingDelegate * delegateInList = (IAAllocationTrackingDelegate *) IAStructArrayList_get(this->delegates, i);
		if (delegateInList == delegate) {
			IAStructArrayList_removeAtIndex(this->delegates, i);
			IA_release(delegateInList);
			debugOnly(isFound = true);
			break;
		}
	}
	debugAssert(isFound == true && "Delegate was not found!");
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_onObjectAllocated(const IAAllocationTrackingEvent * this, const void * objectPointer, size_t allocationSize, const char * className){
	IAAllocationTrackingDelegate * delegate;
	for (size_t i = 0; i < IAStructArrayList_getCurrentSize(this->delegates); i++) {
		delegate = IAStructArrayList_get(this->delegates, i);
		IAAllocationTrackingDelegate_onObjectAllocated(delegate, objectPointer, allocationSize, className);
	}
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_onObjectDeallocated(const IAAllocationTrackingEvent * this, const void * objectPointer, size_t allocationSize, const char * className){
	IAAllocationTrackingDelegate * delegate;
	for (size_t i = 0; i < IAStructArrayList_getCurrentSize(this->delegates); i++) {
		delegate = IAStructArrayList_get(this->delegates, i);
		IAAllocationTrackingDelegate_onObjectDeallocated(delegate, objectPointer, allocationSize, className);
	}
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_onDataAllocated(const IAAllocationTrackingEvent * this, const void * dataPointer, size_t size, const char * className){
	IAAllocationTrackingDelegate * delegate;
	for (size_t i = 0; i < IAStructArrayList_getCurrentSize(this->delegates); i++) {
		delegate = IAStructArrayList_get(this->delegates, i);
		IAAllocationTrackingDelegate_onDataAllocated(delegate, dataPointer, size, className);
	}
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_onDataReallocated(const IAAllocationTrackingEvent * this, const void * oldDataPointer, const void * newDataPointer, size_t newSize, size_t oldSize, const char * className){
	IAAllocationTrackingDelegate * delegate;
	for (size_t i = 0; i < IAStructArrayList_getCurrentSize(this->delegates); i++) {
		delegate = IAStructArrayList_get(this->delegates, i);
		IAAllocationTrackingDelegate_onDataReallocated(delegate, oldDataPointer, newDataPointer, newSize, oldSize, className);
	}
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_onDataDeallocated(const IAAllocationTrackingEvent * this, const void * dataPointer, size_t size, const char * className){
	IAAllocationTrackingDelegate * delegate;
	for (size_t i = 0; i < IAStructArrayList_getCurrentSize(this->delegates); i++) {
		delegate = IAStructArrayList_get(this->delegates, i);
		IAAllocationTrackingDelegate_onDataDeallocated(delegate, dataPointer, size, className);
	}
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_onInitCountIncremented(const IAAllocationTrackingEvent * this, const char * className){
	IAAllocationTrackingDelegate * delegate;
	for (size_t i = 0; i < IAStructArrayList_getCurrentSize(this->delegates); i++) {
		delegate = IAStructArrayList_get(this->delegates, i);
		IAAllocationTrackingDelegate_onInitCountIncremented(delegate, className);
	}
}

/// \memberof IAAllocationTrackingDelegate
static inline void IAAllocationTrackingEvent_onInitCountDecremented(const IAAllocationTrackingEvent * this, const char * className){
	IAAllocationTrackingDelegate * delegate;
	for (size_t i = 0; i < IAStructArrayList_getCurrentSize(this->delegates); i++) {
		delegate = IAStructArrayList_get(this->delegates, i);
		IAAllocationTrackingDelegate_onInitCountDecremented(delegate, className);
	}
}

static inline void IAAllocationTrackingEvent_deinit(IAAllocationTrackingEvent * this){
	IA_STRUCT_ARRAY_LIST_VOID_FREE_WITH_CLASSNAME(this->delegates, "IAAllocationTrackingEvent");
	IA_decrementInitCountForClass("IAAllocationTrackingEvent");
}

static inline void IAAllocationTrackingEvent_autorelease(IAAllocationTrackingEvent * this){
	IA_autorelease(this);
}

static inline void IAAllocationTrackingEvent_release(IAAllocationTrackingEvent * this){
	IA_release(this);
}


#endif

