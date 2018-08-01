//  
//  This file has been automatically generated.
//  
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//  

#ifndef IANotificationEvent_h
#define IANotificationEvent_h

#include "IAStructArrayList.h"
#include "IALibrary.h"
#include "IANotificationDelegate.h"

typedef struct{
	IAStructArrayList * delegates;
} IANotificationEvent;

IA_CONSTRUCTOR static inline void IANotificationEvent_init(IANotificationEvent * this){
	IA_STRUCT_ARRAY_LIST_VOID_MALLOC_MAKE_WITH_CLASSNAME(this->delegates, 8, "IANotificationEvent");
	IA_incrementInitCountForClass("IANotificationEvent");
}

static inline void IANotificationEvent_deinit(IANotificationEvent * this);
IA_CONSTRUCTOR static inline IANotificationEvent * IANotificationEvent_new(){
	IANotificationEvent * this = IA_newWithClassName(sizeof(IANotificationEvent), (void (*)(void *)) IANotificationEvent_deinit, "IANotificationEvent");
	IANotificationEvent_init(this);
	return this;
}

static inline IANotificationEvent * IANotificationEvent_with(){
	IANotificationEvent * this = IANotificationEvent_new();
	IA_autorelease(this);
	return this;
}

/// \memberof IANotificationDelegate
static inline void IANotificationEvent_retain(IANotificationEvent * this){
	IA_retain(this);
}

/// \memberof IANotificationDelegate
static inline void IANotificationEvent_register(IANotificationEvent * this, IANotificationDelegate * delegate){
	IA_retainWithClassName(delegate, "IANotificationDelegate");
	IA_STRUCT_ARRAY_LIST_VOID_REALLOC_MAKE_IF_NEEDED_WITH_CLASSNAME(this->delegates, "IANotificationEvent");
	IAStructArrayList_add(this->delegates, delegate);
}

/// \memberof IANotificationDelegate
static inline void IANotificationEvent_unregister(IANotificationEvent * this, IANotificationDelegate * delegate){
	debugOnly(bool isFound = false;)
	for (size_t i = 0; i < IAStructArrayList_getCurrentSize(this->delegates); i++) {
		IANotificationDelegate * delegateInList = (IANotificationDelegate *) IAStructArrayList_get(this->delegates, i);
		if (delegateInList == delegate) {
			IAStructArrayList_removeAtIndex(this->delegates, i);
			IA_releaseWithClassName(delegateInList, "IANotificationDelegate");
			debugOnly(isFound = true);
			break;
		}
	}
	debugAssert(isFound == true && "Delegate was not found!");
}

/// \memberof IANotificationDelegate
static inline void IANotificationEvent_notify(const IANotificationEvent * this){
	IANotificationDelegate * delegate;
	for (size_t i = 0; i < IAStructArrayList_getCurrentSize(this->delegates); i++) {
		delegate = IAStructArrayList_get(this->delegates, i);
		IANotificationDelegate_notify(delegate);
	}
}

static inline void IANotificationEvent_deinit(IANotificationEvent * this){
	IA_STRUCT_ARRAY_LIST_VOID_FREE_WITH_CLASSNAME(this->delegates, "IANotificationEvent");
	IA_decrementInitCountForClass("IANotificationEvent");
}

static inline void IANotificationEvent_autorelease(IANotificationEvent * this){
	IA_autorelease(this);
}

static inline void IANotificationEvent_release(IANotificationEvent * this){
	IA_release(this);
}


#endif

