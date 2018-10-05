#include "IALibrary.h"
#include "IAJni.h"
#include "IARecursiveLock.h"
#include "IAHashMap.h"
#include "IALock.h"
#include "JNIEnv+HelperMethods.h"
#include "IACharArray.h"

#include <unistd.h>

#define CLASSNAME "IAJni"


static JavaVM * vm = NULL;
static JNIEnv * envForApplication = NULL;
static pid_t envThreadId;
static IAHashMap * otherEnvs;

static IARecursiveLock * applicationEntranceLock = NULL;
static IALock * envLock = NULL;

static jobject jClassLoader;
static jmethodID jLoadClass;


void IAJni_commence(JNIEnv * env){
	(*env)->GetJavaVM(env, &vm);
	otherEnvs = IAHashMap_new(8);
	applicationEntranceLock = IARecursiveLock_new();
	envLock = IALock_new();

	jclass jLibraryClass = (*env)->FindClass(env, "com/impsapps/impsengine/common/clib/Library");
	jclass jClassRef = (*env)->GetObjectClass(env, jLibraryClass);
	jclass jClassLoaderClass = (*env)->FindClass(env, "java/lang/ClassLoader");
	jmethodID getClassLoader = (*env)->GetMethodID(env, jClassRef, "getClassLoader", "()Ljava/lang/ClassLoader;");

	jobject jClassLoaderLocal = (*env)->CallObjectMethod(env, jLibraryClass, getClassLoader);
	jLoadClass = (*env)->GetMethodID(env, jClassLoaderClass, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
	jClassLoader = (*env)->NewGlobalRef(env, jClassLoaderLocal);

	(*env)->DeleteLocalRef(env, jClassLoaderLocal);
	(*env)->DeleteLocalRef(env, jClassLoaderClass);
	(*env)->DeleteLocalRef(env, jClassRef);
	(*env)->DeleteLocalRef(env, jLibraryClass);
}

JavaVM* IAJni_getJavaVM(void){
	return vm;
}

jclass IAJni_loadClass(JNIEnv * env, const char * className){
	jstring jName = JNIEnv_createStringWithUTFCharsLocally(env, className);
	jclass jClass = (*env)->CallObjectMethod(env, jClassLoader, jLoadClass, jName);
	debugAssert((*env)->ExceptionCheck(env) == JNI_FALSE && "Class could not be loaded");
	JNIEnv_destroyStringWithUTFCharsLocally(env, jName);
	return jClass;
}

void IAJni_acquireApplicationEntrance(JNIEnv * env){
	IARecursiveLock_lock(applicationEntranceLock);
	synchronized(envLock){
        envForApplication = env;
		envThreadId = gettid();
	}
}

void IAJni_addJNIEnvForAsyncThread(JNIEnv * env){
	pid_t threadId = gettid();
	char str[IA_MAX_BUFFER_UINT64];
	IACharArray_setUInt64(str, threadId);
	synchronized(envLock){
		IAHashMap_add(otherEnvs, str, env);
	}
}

JNIEnv * IAJni_getJNIEnv(void){
	JNIEnv * env = NULL;
    pid_t threadId = gettid();
	synchronized(envLock){
		if (envThreadId == threadId){
            env = envForApplication;
		}else{
			char str[IA_MAX_BUFFER_UINT64];
			IACharArray_setUInt64(str, threadId);
            env = IAHashMap_get(otherEnvs, str);
		}
	}
	return env;
}

void IAJni_removeJNIEnvForAsyncThread(void){
    pid_t threadId = gettid();
    char str[IA_MAX_BUFFER_UINT64];
    IACharArray_setUInt64(str, threadId);
	synchronized(envLock) {
		IAHashMap_remove(otherEnvs, str);
	}
}

void IAJni_dispenseApplicationEntrance(void){
	IARecursiveLock_unlock(applicationEntranceLock);
}

void IAJni_terminate(void){
	envForApplication = NULL;
	vm = NULL;
	IAHashMap_release(otherEnvs);
	IARecursiveLock_release(applicationEntranceLock);
	IALock_release(envLock);
	applicationEntranceLock = NULL;
}
