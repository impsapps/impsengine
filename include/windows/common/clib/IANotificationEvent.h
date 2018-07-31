//  
//  This file has been automatically generated.
//  
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//  

#ifndef IANotificationEvent_h
#define IANotificationEvent_h

#include "IAArrayList.h"
#include "IAArrayListIterator.h"
#include "IALibrary.h"
#include "IANotificationDelegate.h"

typedef struct{
	IAArrayList delegates;
} IANotificationEvent;

IA_CONSTRUCTOR static inline void IANotificationEvent_init(IANotificationEvent * this){
	IAArrayList_init(&this->delegates, 8);
	IA_incrementInitCountForClass("IANotificationEvent");
}

static inline void IANotificationEvent_deinit(IANotificationEvent * this);
IA_CONSTRUCTOR static inline IANotificationEvent * IANotificationEvent_new(){
	IANotificationEvent * this = IA_newWithClassName(sizeof(IANotificationEvent), (void (*)(void *)) IANotificationEvent_deinit, "IANotificationEvent");
	IANotificationEvent_init(this);
	return this;
}

/// \memberof IANotificationDelegate
static inline void IANotificationEvent_retain(IANotificationEvent * this){
	IA_retain(this);
}

/// \memberof IANotificationDelegate
static inline void IANotificationEvent_register(IANotificationEvent * this, IANotificationDelegate * delegate){
	IAArrayList_add(&this->delegates, delegate);
}

/// \memberof IANotificationDelegate
static inline IANotificationDelegate * IANotificationEvent_unregister(IANotificationEvent * this, IANotificationDelegate * delegate){
	return IAArrayList_removeObject(&this->delegates, delegate);
}

/// \memberof IANotificationDelegate
static inline void IANotificationEvent_notify(const IANotificationEvent * this){
	IANotificationDelegate * delegate;
	foreach (delegate in arrayList(&this->delegates)) {
		IANotificationDelegate_notify(delegate);
	}
}

static inline void IANotificationEvent_deinit(IANotificationEvent * this){
	IAArrayList_deinit(&this->delegates);
	IA_decrementInitCountForClass("IANotificationEvent");
}

static inline void IANotificationEvent_release(IANotificationEvent * this){
	IA_release(this);
}


#endif

