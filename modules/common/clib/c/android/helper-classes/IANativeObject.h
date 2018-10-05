#ifndef IANativeObject_h
#define IANativeObject_h

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
