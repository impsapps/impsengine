//
//  IAJni.h
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on 23.04.2015.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#ifndef ImpsEngineAndroid_IAJniEnv_h
#define ImpsEngineAndroid_IAJniEnv_h

#include <jni.h>

void IAJni_commence(JNIEnv * env);

JavaVM* IAJni_getJavaVM(void);

jclass IAJni_loadClass(JNIEnv * env, const char * className);

void IAJni_acquireApplicationEntrance(JNIEnv * env);

void IAJni_addJNIEnvForAsyncThread(JNIEnv * env);
JNIEnv * IAJni_getJNIEnv(void);
void IAJni_removeJNIEnvForAsyncThread(void);

void IAJni_dispenseApplicationEntrance(void);

void IAJni_terminate(void);

#endif
