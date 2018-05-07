//
//  IABundleInfo.c
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on May 7, 2018.
//  Copyright (c) 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include <string.h>
#include "IALibrary.h"
#include "IABundleInfo.h"
#include "JNIEnv+HelperMethods.h"
#include "IAJni.h"

#define CLASSNAME "IABundleInfo"

static jclass jBundleInfoClass;

static jmethodID getAppVersion;

static bool isCommenced;

static void IABundleInfo_commenceJniIfNeeded(JNIEnv * env){
    if (isCommenced == false){
        isCommenced = true;
        jBundleInfoClass = JNIEnv_createNativeClass(env, "com/impsapps/impsengine/misc/bundleinfo/BundleInfo");
        getAppVersion = (*env)->GetStaticMethodID(env, jBundleInfoClass, "getAppVersion", "()Ljava/lang/String;");
    }
}

const char * IABundleInfo_getAppVersion(){
    static char * appVersion = NULL;
    if (appVersion == NULL){
        JNIEnv * env = IAJni_getJNIEnv();
        IABundleInfo_commenceJniIfNeeded(env);
        jstring jAppVersion = (*env)->CallStaticObjectMethod(env, jBundleInfoClass, getAppVersion);
        const char * nativeAppVersion = JNIEnv_createUTFChars(env, jAppVersion);
        size_t str_len = strlen(nativeAppVersion);
        appVersion = IA_malloc(str_len + 1);
        memcpy(appVersion, nativeAppVersion, str_len + 1);
        JNIEnv_destroyLocalRef(env, jAppVersion);
    }
    return appVersion;
}
