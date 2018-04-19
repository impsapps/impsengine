//
//  IANativeObject.h
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on 07.06.2015.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#ifndef ImpsEngineAndroid_IANativeObject_h
#define ImpsEngineAndroid_IANativeObject_h

#include <jni.h>

typedef struct{
	jobject jObject;
} IANativeObject;

void IANativeObject_init(IANativeObject * nativeObject, JNIEnv * env, jobject object);

void IANativeObject_updateJObject(IANativeObject * nativeObject, JNIEnv * env, jobject object);
jobject IANativeObject_getJObject(IANativeObject * nativeObject);

void IANativeObject_deinit(IANativeObject * nativeObject, JNIEnv * env);

#include "IANativeObject+Generated.h"

#endif
