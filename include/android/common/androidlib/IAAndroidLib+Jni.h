//
//  IAAndroidLib.h
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on 04.05.2015.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#ifndef ImpsEngineAndroid_IAAndroidLib_h
#define ImpsEngineAndroid_IAAndroidLib_h

#include "IAJni.h"

void IAAndroidLib_commenceJni(JNIEnv * env);

jclass IAAndroidLib_getImpsEngineClass();
jmethodID IAAndroidLib_getMethodIDForGetAppState();

jclass IAAndroidLib_getAppstateClass();
jmethodID IAAndroidLib_getMethodIDForGetActivity();
jmethodID IAAndroidLib_getMethodIDForGetAssetManager();
jmethodID IAAndroidLib_getMethodIDForGetContext();
jmethodID IAAndroidLib_getMethodIDForGetResources();

jclass IAAndroidLib_getStringClass();

jclass IAAndroidLib_getContextClass();
jmethodID IAAndroidLib_getMethodIDForGetContentResolver();

jclass IAAndroidLib_getResolverClass();

void IAAndroidLib_terminateJni(JNIEnv * env);

#endif
