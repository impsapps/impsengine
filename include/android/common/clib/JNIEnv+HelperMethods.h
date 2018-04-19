//
//  JNIEnv+HelperMethods.h
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on ${date}.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#ifndef ImpsEngineAndroid_JNIEnvHelperExt_h
#define ImpsEngineAndroid_JNIEnvHelperExt_h

#include <jni.h>
#include <stdbool.h>

jclass JNIEnv_createNativeClass(JNIEnv * env, const char * className);
jclass JNIEnv_createNativeClassInPackage(JNIEnv * env, const char * className, const char * packageName);
void JNIEnv_destroyNativeClass(JNIEnv * env, jclass nativeClass);

jmethodID JNIEnv_getNativeMethodIDForConstructor(JNIEnv *env, jclass nativeClass, const char *signature);

const char * JNIEnv_createUTFChars(JNIEnv * env, jstring nativeString);
void JNIEnv_destroyUTFChars(JNIEnv * env, jstring nativeString, const char * utfChars);

jstring JNIEnv_createStringWithUTFCharsLocally(JNIEnv * env, const char * utfChars);
void JNIEnv_destroyStringWithUTFCharsLocally(JNIEnv * env, jstring nativeString);

jobject JNIEnv_createGlobalRef(JNIEnv * env, jobject nativeObject);
void JNIEnv_destroyGlobalRef(JNIEnv * env, jobject nativeObject);

//destroy all local references on java objects with this function
void JNIEnv_destroyLocalRef(JNIEnv * env, jobject nativeObject);

#endif
