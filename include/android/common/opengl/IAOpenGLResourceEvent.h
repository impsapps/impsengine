//  
//  This file has been automatically generated.
//  
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//  

#ifndef IAOpenGLResourceEvent_h
#define IAOpenGLResourceEvent_h

#include "IAStructArrayList.h"
#include "IALibrary.h"
#include "IAOpenGLResourceDelegate.h"

typedef struct{
	IAStructArrayList * delegates;
} IAOpenGLResourceEvent;

IA_CONSTRUCTOR static inline void IAOpenGLResourceEvent_init(IAOpenGLResourceEvent * this){
	IA_STRUCT_ARRAY_LIST_VOID_MALLOC_MAKE_WITH_CLASSNAME(this->delegates, 8, "IAOpenGLResourceEvent");
	IA_incrementInitCountForClass("IAOpenGLResourceEvent");
}

static inline void IAOpenGLResourceEvent_deinit(IAOpenGLResourceEvent * this);
IA_CONSTRUCTOR static inline IAOpenGLResourceEvent * IAOpenGLResourceEvent_new(){
	IAOpenGLResourceEvent * this = IA_newWithClassName(sizeof(IAOpenGLResourceEvent), (void (*)(void *)) IAOpenGLResourceEvent_deinit, "IAOpenGLResourceEvent");
	IAOpenGLResourceEvent_init(this);
	return this;
}

static inline IAOpenGLResourceEvent * IAOpenGLResourceEvent_with(){
	IAOpenGLResourceEvent * this = IAOpenGLResourceEvent_new();
	IA_autorelease(this);
	return this;
}

/// \memberof IAOpenGLResourceDelegate
static inline void IAOpenGLResourceEvent_retain(IAOpenGLResourceEvent * this){
	IA_retain(this);
}

/// \memberof IAOpenGLResourceDelegate
static inline void IAOpenGLResourceEvent_register(IAOpenGLResourceEvent * this, IAOpenGLResourceDelegate * delegate){
	IA_STRUCT_ARRAY_LIST_VOID_REALLOC_MAKE_IF_NEEDED_WITH_CLASSNAME(this->delegates, "IAOpenGLResourceEvent");
	IAStructArrayList_add(this->delegates, delegate);
}

/// \memberof IAOpenGLResourceDelegate
static inline void IAOpenGLResourceEvent_unregister(IAOpenGLResourceEvent * this, IAOpenGLResourceDelegate * delegate){
	debugOnly(bool isFound = false;)
	for (size_t i = 0; i < IAStructArrayList_getCurrentSize(this->delegates); i++) {
		IAOpenGLResourceDelegate * delegateInList = (IAOpenGLResourceDelegate *) IAStructArrayList_get(this->delegates, i);
		if (delegateInList == delegate) {
			IAStructArrayList_removeAtIndex(this->delegates, i);
			debugOnly(isFound = true);
			break;
		}
	}
	debugAssert(isFound == true && "Delegate was not found!");
}

/// \memberof IAOpenGLResourceDelegate
static inline void IAOpenGLResourceEvent_createResources(const IAOpenGLResourceEvent * this){
	IAOpenGLResourceDelegate * delegate;
	for (size_t i = 0; i < IAStructArrayList_getCurrentSize(this->delegates); i++) {
		delegate = IAStructArrayList_get(this->delegates, i);
		IAOpenGLResourceDelegate_createResources(delegate);
	}
}

/// \memberof IAOpenGLResourceDelegate
static inline void IAOpenGLResourceEvent_destroyResources(const IAOpenGLResourceEvent * this){
	IAOpenGLResourceDelegate * delegate;
	for (size_t i = 0; i < IAStructArrayList_getCurrentSize(this->delegates); i++) {
		delegate = IAStructArrayList_get(this->delegates, i);
		IAOpenGLResourceDelegate_destroyResources(delegate);
	}
}

static inline void IAOpenGLResourceEvent_deinit(IAOpenGLResourceEvent * this){
	IA_STRUCT_ARRAY_LIST_VOID_FREE_WITH_CLASSNAME(this->delegates, "IAOpenGLResourceEvent");
	IA_decrementInitCountForClass("IAOpenGLResourceEvent");
}

static inline void IAOpenGLResourceEvent_autorelease(IAOpenGLResourceEvent * this){
	IA_autorelease(this);
}

static inline void IAOpenGLResourceEvent_release(IAOpenGLResourceEvent * this){
	IA_release(this);
}


#endif

