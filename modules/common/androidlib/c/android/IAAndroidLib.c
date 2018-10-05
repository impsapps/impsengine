#include "IAJni.h"
#include "JNIEnv+HelperMethods.h"
#include "IAAndroidLib+Jni.h"

#define CLASSNAME "IAAndroidLib"


static jclass jImpsEngineClass;
static jmethodID jGetAppState;

static jclass jAppstateClass;
static jmethodID jGetActivity;
static jmethodID jGetAssetManager;
static jmethodID jGetContext;
static jmethodID jGetResources;

static jclass jStringClass;

static jclass jContextClass;
static jmethodID jGetContentResolver;

static jclass jContentResolverClass;


void IAAndroidLib_commenceJni(JNIEnv * env){
	jImpsEngineClass = JNIEnv_createNativeClass(env, "com/impsapps/impsengine/common/androidlib/ImpsEngine");
	jGetAppState = (*env)->GetStaticMethodID(env, jImpsEngineClass, "getAppState", "()Lcom/impsapps/impsengine/common/androidlib/AppState;");

	jAppstateClass = JNIEnv_createNativeClass(env, "com/impsapps/impsengine/common/androidlib/AppState");
	jGetActivity = (*env)->GetMethodID(env, jAppstateClass, "getActivity", "()Landroid/app/Activity;");
	jGetAssetManager = (*env)->GetMethodID(env, jAppstateClass, "getAssetManager", "()Landroid/content/res/AssetManager;");
	jGetContext = (*env)->GetMethodID(env, jAppstateClass, "getContext", "()Landroid/content/Context;");
	jGetResources = (*env)->GetMethodID(env, jAppstateClass, "getResources", "()Landroid/content/res/Resources;");

	jStringClass = JNIEnv_createNativeClass(env, "java/lang/String");

	jContextClass = JNIEnv_createNativeClass(env, "android/content/Context");
    jGetContentResolver = (*env)->GetMethodID(env, jContextClass, "getContentResolver", "()Landroid/content/ContentResolver;");

	jContentResolverClass = JNIEnv_createNativeClass(env, "android/content/ContentResolver");
}

jclass IAAndroidLib_getImpsEngineClass(){
	return jImpsEngineClass;
}

jmethodID IAAndroidLib_getMethodIDForGetAppState(){
	return jGetAppState;
}

jclass IAAndroidLib_getAppstateClass(){
	return jAppstateClass;
}

jmethodID IAAndroidLib_getMethodIDForGetActivity(){
	return jGetActivity;
}

jmethodID IAAndroidLib_getMethodIDForGetAssetManager(){
	return jGetAssetManager;
}

jmethodID IAAndroidLib_getMethodIDForGetContext(){
	return jGetContext;
}

jmethodID IAAndroidLib_getMethodIDForGetResources(){
	return jGetResources;
}

jclass IAAndroidLib_getStringClass(){
	return jStringClass;
}

jclass IAAndroidLib_getContextClass(){
	return jContextClass;
}

jmethodID IAAndroidLib_getMethodIDForGetContentResolver(){
    return jGetContentResolver;
}

jclass IAAndroidLib_getResolverClass(){
	return jContentResolverClass;
}

void IAAndroidLib_terminateJni(JNIEnv * env){
	JNIEnv_destroyNativeClass(env, jImpsEngineClass);
	JNIEnv_destroyNativeClass(env, jAppstateClass);
	JNIEnv_destroyNativeClass(env, jStringClass);
	JNIEnv_destroyNativeClass(env, jContextClass);
	JNIEnv_destroyNativeClass(env, jContentResolverClass);
}
