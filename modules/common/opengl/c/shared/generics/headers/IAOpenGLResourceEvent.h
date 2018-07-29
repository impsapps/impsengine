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
#include "IAOpenGLResourceDelegate.h"

typedef struct{
	IAArrayList delegates;
} IAOpenGLResourceEvent;

IA_CONSTRUCTOR static inline void IAOpenGLResourceEvent_init(IAOpenGLResourceEvent * this){
	IAArrayList_init(&this->delegates, 8);
	IA_incrementInitCountForClass("IAOpenGLResourceEvent");
}

static inline void IAOpenGLResourceEvent_deinit(IAOpenGLResourceEvent * this);
IA_CONSTRUCTOR static inline IAOpenGLResourceEvent * IAOpenGLResourceEvent_new(){
	IAOpenGLResourceEvent * this = IA_newWithClassName(sizeof(IAOpenGLResourceEvent), (void (*)(void *)) IAOpenGLResourceEvent_deinit, "IAOpenGLResourceEvent");
	IAOpenGLResourceEvent_init(this);
	return this;
}

/// \memberof IAOpenGLResourceDelegate
static inline void IAOpenGLResourceEvent_retain(IAOpenGLResourceEvent * this){
	IA_retain(this);
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

static inline void IAOpenGLResourceEvent_deinit(IAOpenGLResourceEvent * this){
	IAArrayList_deinit(&this->delegates);
	IA_decrementInitCountForClass("IAOpenGLResourceEvent");
}

static inline void IAOpenGLResourceEvent_release(IAOpenGLResourceEvent * this){
	IA_release(this);
}


#endif

