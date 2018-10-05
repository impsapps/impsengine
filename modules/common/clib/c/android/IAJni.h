#ifndef IAJni_h
#define IAJni_h

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
