//
//  
//  ImpsEngine
//
//  Created by Konstantin Merker on 13.12.17.
//  Copyright (c) 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAShare.h"
#include "JNIEnv+HelperMethods.h"
#include "IAJni.h"
#include "IANativeObject.h"
#include "IABitmap+Native.h"

static jclass jShareClass;

static jmethodID share;

static bool isCommenced;

void IAShare_commenceJniIfNeeded(JNIEnv * env){
    if (isCommenced == false){
        isCommenced = true;
        jShareClass = JNIEnv_createNativeClass(env, "com/impsapps/impsengine/utilities/url/Share");
        share = (*env)->GetStaticMethodID(env, jShareClass, "share", "(Ljava/lang/String;Landroid/graphics/Bitmap;)V");
    }
}

void IAShare_shareBitmap(const char * text, IABitmap * bitmap){
    JNIEnv * env = IAJni_getJNIEnv();
    IAShare_commenceJniIfNeeded(env);
    jstring jText = JNIEnv_createStringWithUTFCharsLocally(env, text);
    IANativeObject * nativeBitmap = IABitmap_getBitmapRef(bitmap);
    jobject jIABitmap = IANativeObject_getJObject(nativeBitmap);
    (*env)->CallStaticVoidMethod(env, jShareClass, share, jText, jIABitmap);
    JNIEnv_destroyStringWithUTFCharsLocally(env, jText);
}


