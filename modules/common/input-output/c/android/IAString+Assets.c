//
//  IAString+Assets.h
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on 23.04.2015.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAAndroidLib+Jni.h"
#include "IAString.h"
#include "JNIEnv+HelperMethods.h"

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#define CLASSNAME "IAString"


void IAString_nativeInitWithAsset(IAString * this, const char * assetName, const char * assetFileExtension){
	long lengthOfAssetName = strlen(assetName);
	long lengthOfAssetFileExtension = strlen(assetFileExtension);
	char assetFile[lengthOfAssetName + lengthOfAssetFileExtension + 2];
	long i;
	for (i = 0; i < lengthOfAssetName; i++) {
		assetFile[i] = assetName[i];
	}
	assetFile[i] = '.';
	i++;
	for(long j = 0; j < lengthOfAssetFileExtension; j++){
		assetFile[i] = assetFileExtension[j];
		i++;
	}
	assetFile[i] = '\0';

#if DEBUG == true
    assert(strlen(assetFile) == lengthOfAssetName + lengthOfAssetFileExtension + 1);
#endif

	JNIEnv * env = IAJni_getJNIEnv();

	jclass jImpsEngineClass = IAAndroidLib_getImpsEngineClass();
	jmethodID jGetAppState = IAAndroidLib_getMethodIDForGetAppState();
	jobject jAppState = (*env)->CallStaticObjectMethod(env, jImpsEngineClass, jGetAppState);

	jmethodID jGetAssetManager = IAAndroidLib_getMethodIDForGetAssetManager();
	jobject jAssetManager = (*env)->CallObjectMethod(env, jAppState, jGetAssetManager);

	AAssetManager* aAssetManager = AAssetManager_fromJava(env, jAssetManager);
    AAsset* asset = AAssetManager_open(aAssetManager, assetFile, AASSET_MODE_BUFFER);
    assert(asset != NULL && "Can't open asset!");
    off_t size = AAsset_getLength(asset);
	this->c = IA_malloc(sizeof(char) * (size + 1));
	this->arraySize = size + 1;
	this->length = size;

    AAsset_read (asset,this->c,size);
	this->c[size] = '\0';

    AAsset_close(asset);
    JNIEnv_destroyLocalRef(env, jAssetManager);
    JNIEnv_destroyLocalRef(env, jAppState);
}