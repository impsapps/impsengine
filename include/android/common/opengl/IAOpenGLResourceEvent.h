//  
//  This file has been automatically generated.
//  
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//  

#ifndef IAOpenGLResourceEvent_h
#define IAOpenGLResourceEvent_h

#include "IAArrayList.h"
#include "IAArrayListIterator.h"
#include "IALibrary.h"

typedef struct{
	IAArrayList delegates;
} IAOpenGLResourceEvent;

IA_CONSTRUCTOR static inline void IAOpenGLResourceEvent_init(IAOpenGLResourceEvent * this){
	IAArrayList_init(&this->delegates, 8);
	IA_increaseAllocationCountForClass("IAOpenGLResourceEvent");
}

IA_CONSTRUCTOR static inline IAOpenGLResourceEvent * IAOpenGLResourceEvent_new(){
	IAOpenGLResourceEvent * this = IA_mallocWithClassName(sizeof(IAOpenGLResourceEvent), "IAOpenGLResourceEvent");
	IAOpenGLResourceEvent_init(this);
	return this;
}

/// \memberof IAOpenGLResourceDelegate
static inline void IAOpenGLResourceEvent_register(IAOpenGLResourceEvent * this, IAOpenGLResourceDelegate * delegate){
	IAArrayList_add(&this->delegates, delegate);
}

/// \memberof IAOpenGLResourceDelegate
static inline IAOpenGLResourceDelegate * IAOpenGLResourceEvent_unregister(IAOpenGLResourceEvent * this, IAOpenGLResourceDelegate * delegate){
	return IAArrayList_removeObject(&this->delegates, delegate);
}

/// \memberof IAOpenGLResourceDelegate
static inline void IAOpenGLResourceEvent_createResources(const IAOpenGLResourceEvent * this){
	IAOpenGLResourceDelegate * delegate;
	foreach (delegate in arrayList(&this->delegates)) {
		IAOpenGLResourceDelegate_createResources(delegate);
	}
}

/// \memberof IAOpenGLResourceDelegate
static inline void IAOpenGLResourceEvent_destroyResources(const IAOpenGLResourceEvent * this){
	IAOpenGLResourceDelegate * delegate;
	foreach (delegate in arrayList(&this->delegates)) {
		IAOpenGLResourceDelegate_destroyResources(delegate);
	}
}

IA_DESTRUCTOR static inline void IAOpenGLResourceEvent_deinit(IAOpenGLResourceEvent * this){
	IAArrayList_deinit(&this->delegates);
	IA_decreaseAllocationCountForClass("IAOpenGLResourceEvent");
}

IA_DESTRUCTOR static inline void IAOpenGLResourceEvent_release(IAOpenGLResourceEvent * this){
	IAOpenGLResourceEvent_deinit(this);
	IA_freeWithClassName(this, "IAOpenGLResourceEvent");
}


#endif

