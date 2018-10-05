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

