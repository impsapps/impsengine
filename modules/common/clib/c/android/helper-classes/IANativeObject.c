//
//  IANativeObject.c
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on 07.06.2015.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IANativeObject.h"
#include "IALibrary.h"
#include "IAAllocationTracker.h"

#define CLASSNAME "IANativeObject"


void IANativeObject_init(IANativeObject * nativeObject, JNIEnv * env, jobject object){
	nativeObject->jObject = (*env)->NewGlobalRef(env, object);
	IA_increaseAllocationCount();
}

void IANativeObject_updateJObject(IANativeObject * nativeObject, JNIEnv * env, jobject object){
	(*env)->DeleteGlobalRef(env, nativeObject->jObject);
	nativeObject->jObject = (*env)->NewGlobalRef(env, object);
}

jobject IANativeObject_getJObject(IANativeObject * nativeObject){
	return nativeObject->jObject;
}

void IANativeObject_deinit(IANativeObject * nativeObject, JNIEnv * env){
	(*env)->DeleteGlobalRef(env, nativeObject->jObject);
    IA_decreaseAllocationCount();
}

