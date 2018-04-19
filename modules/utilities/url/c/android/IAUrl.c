//
//  Url.c
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on Mar 25, 2016.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IALibrary.h"
#include "IAUrl.h"
#include "JNIEnv+HelperMethods.h"
#include "IAJni.h"

static jclass jUrlClass;

static jmethodID openUrlInWebview;
static jmethodID openReviewPageInAppstore;

static bool isCommenced;

void IAUrl_commenceJniIfNeeded(JNIEnv * env){
    if (isCommenced == false){
        isCommenced = true;
        jUrlClass = JNIEnv_createNativeClass(env, "com/impsapps/impsengine/utilities/url/Url");
        openUrlInWebview = (*env)->GetStaticMethodID(env, jUrlClass, "openUrlInWebview", "(Ljava/lang/String;)V");
        openReviewPageInAppstore = (*env)->GetStaticMethodID(env, jUrlClass, "openReviewPageInAppstore", "()V");
    }
}

void IAUrl_openUrlInWebview(const char * url){
    JNIEnv * env = IAJni_getJNIEnv();
    IAUrl_commenceJniIfNeeded(env);
    jstring jUrl = JNIEnv_createStringWithUTFCharsLocally(env, url);
    (*env)->CallStaticVoidMethod(env, jUrlClass, openUrlInWebview, jUrl);
    JNIEnv_destroyStringWithUTFCharsLocally(env, jUrl);
}

void IAUrl_openReviewPageInAppstore(const char * iosAppStoreId){
    JNIEnv * env = IAJni_getJNIEnv();
    IAUrl_commenceJniIfNeeded(env);
    (*env)->CallStaticVoidMethod(env, jUrlClass, openReviewPageInAppstore);
}
