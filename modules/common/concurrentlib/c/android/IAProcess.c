//
//  IAProcess.c
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on Nov 1, 2015.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IAProcess+AndroidNative.h"

#include "IAJni.h"
#include "IALibrary.h"

#define CLASSNAME "IAProcess"


void IAProcess_attachToJavaVM(){
	JavaVM * vm = IAJni_getJavaVM();
	JNIEnv * env = NULL;
	if ((*vm)->AttachCurrentThread(vm, &env, NULL) != 0) {
		logError("Can't attach current thread");
	}
	IAJni_addJNIEnvForAsyncThread(env);
}

void IAProcess_detachFromJavaVM(){
	JavaVM * vm = IAJni_getJavaVM();
	(*vm)->DetachCurrentThread(vm);
	IAJni_removeJNIEnvForAsyncThread();
}

