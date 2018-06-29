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
	IA_increaseAllocationCountForClass("IANotificationEvent");
}

IA_CONSTRUCTOR static inline IANotificationEvent * IANotificationEvent_new(){
	IANotificationEvent * this = IA_mallocWithClassName(sizeof(IANotificationEvent), "IANotificationEvent");
	IANotificationEvent_init(this);
	return this;
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

IA_DESTRUCTOR static inline void IANotificationEvent_deinit(IANotificationEvent * this){
	IAArrayList_deinit(&this->delegates);
	IA_decreaseAllocationCountForClass("IANotificationEvent");
}

IA_DESTRUCTOR static inline void IANotificationEvent_release(IANotificationEvent * this){
	IANotificationEvent_deinit(this);
	IA_freeWithClassName(this, "IANotificationEvent");
}


#endif

