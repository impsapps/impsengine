#include "IALibrary.h"
#include "JNIEnv+HelperMethods.h"
#include "IAJni.h"
#include "IAAllocationTracker.h"
#include <string.h>

#define CLASSNAME "JNIEnv"
#define NATIVEUTFCHARS "JNIEnv - UTFChars"
#define NATIVESTRING "JNIEnv - jstring"
#define NATIVEGLOBALREFERENCE "JNIEnv - globalReference"


jclass JNIEnv_createNativeClass(JNIEnv * env, const char * className){
	jclass localClass = IAJni_loadClass(env, className);
    jclass globalClass = (*env)->NewGlobalRef(env, localClass);
    (*env)->DeleteLocalRef(env, localClass);
    return globalClass;
}

jclass JNIEnv_createNativeClassInPackage(JNIEnv * env, const char * className, const char * packageName){
	int lengthOfClassName = strlen(className);
	int lengthOfPackageName = strlen(packageName);
	char name[lengthOfClassName + lengthOfPackageName + 2];
	memcpy(name, packageName, lengthOfPackageName);
	name[lengthOfPackageName] = '/';
	memcpy(&name[lengthOfPackageName + 1], className, lengthOfClassName);
	name[lengthOfClassName + lengthOfPackageName + 1] = '\0';
	return JNIEnv_createNativeClass(env, name);
}

void JNIEnv_destroyNativeClass(JNIEnv * env, jclass nativeClass){
    (*env)->DeleteGlobalRef(env, nativeClass);
}

jmethodID JNIEnv_getNativeMethodIDForConstructor(JNIEnv *env, jclass nativeClass, const char *signature){
	//signature like: "()V"
	return (*env)->GetMethodID(env, nativeClass, "<init>", signature);
}

const char * JNIEnv_createUTFChars(JNIEnv * env, jstring nativeString){
#if DEBUG == true
	IAAllocationTracker_objectAllocated(NATIVEUTFCHARS);
#endif
	return (*env)->GetStringUTFChars(env, nativeString, 0);
}

void JNIEnv_destroyUTFChars(JNIEnv * env, jstring nativeString, const char * utfChars){
#if DEBUG == true
	IAAllocationTracker_objectDeallocated(NATIVEUTFCHARS);
#endif
	(*env)->ReleaseStringUTFChars(env, nativeString, utfChars);
}

jstring JNIEnv_createStringWithUTFCharsLocally(JNIEnv * env, const char * utfChars){
#if DEBUG == true
	IAAllocationTracker_objectAllocated(NATIVESTRING);
#endif
	return (*env)->NewStringUTF(env, utfChars);
}

void JNIEnv_destroyStringWithUTFCharsLocally(JNIEnv * env, jstring nativeString){
#if DEBUG == true
	IAAllocationTracker_objectDeallocated(NATIVESTRING);
#endif
	(*env)->DeleteLocalRef(env, nativeString);
}

jobject JNIEnv_createGlobalRef(JNIEnv * env, jobject nativeObject){
#if DEBUG == true
	IAAllocationTracker_objectAllocated(NATIVEGLOBALREFERENCE);
#endif
	return (*env)->NewGlobalRef(env, nativeObject);
}

void JNIEnv_destroyGlobalRef(JNIEnv * env, jobject nativeObject){
#if DEBUG == true
	IAAllocationTracker_objectDeallocated(NATIVEGLOBALREFERENCE);
#endif
	(*env)->DeleteGlobalRef(env, nativeObject);
}

void JNIEnv_destroyLocalRef(JNIEnv * env, jobject nativeObject){
	(*env)->DeleteLocalRef(env, nativeObject);
}

