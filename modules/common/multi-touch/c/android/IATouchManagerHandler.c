//
//  IATouchManagerJniExt.c
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on Nov 11, 2015.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IALibrary.h"
#include "com_impsapps_impsengine_common_multitouch_TouchListener.h"
#include "IATouchManagerHandler+Jni.h"
#include "IATouchManager.h"

#include "IAJni.h"

#define CLASSNAME "IATouchManagerHandler"


//used to buffer touch handlers for touchMoved
static size_t currentLengthOfTouchHandlersTemp;
static size_t maxLengthOfTouchHandlersTemp;
static IATouchHandler ** touchHandlersTemp;

void IATouchManagerHandler_commenceJni(JNIEnv * env){
	maxLengthOfTouchHandlersTemp = 5;
	touchHandlersTemp = IA_malloc(sizeof(IATouchHandler *) * maxLengthOfTouchHandlersTemp);
}

JNIEXPORT void JNICALL Java_com_impsapps_impsengine_common_multitouch_TouchListener_createNewTouchHandler(JNIEnv * env, jclass nativeClass, jlong touchId, jfloat pointX, jfloat pointY){
	IATouchManager_createNewTouchHandler((long) touchId, IAPoint_make((float) pointX, (float) pointY));
}

JNIEXPORT void JNICALL Java_com_impsapps_impsengine_common_multitouch_TouchListener_onTouchBegan(JNIEnv * env, jclass nativeClass, jlong touchId, jfloat pointX, jfloat pointY){
	IAJni_acquireApplicationEntrance(env);
	IATouchHandler * touchHandler = IATouchManager_getTouchHandler((long) touchId);
	IATouchHandler_setTouchLocation(touchHandler, IAPoint_make((float) pointX, (float) pointY));

	size_t lengthOfTouchHandlers = 1;
	IATouchHandler * touchHandlers[lengthOfTouchHandlers];
	touchHandlers[0] = touchHandler;
	IATouchManager_onTouchBegan(lengthOfTouchHandlers, touchHandlers);
	IAJni_dispenseApplicationEntrance();
}

JNIEXPORT void JNICALL Java_com_impsapps_impsengine_common_multitouch_TouchListener_prepareOnTouchMoved(JNIEnv * env, jclass nativeClass, jint numberOfTouches){
	while (numberOfTouches > maxLengthOfTouchHandlersTemp){
		maxLengthOfTouchHandlersTemp *= 2;
		touchHandlersTemp = realloc(touchHandlersTemp, sizeof(IATouchHandler *) * maxLengthOfTouchHandlersTemp);
	}
	currentLengthOfTouchHandlersTemp = 0;
}

JNIEXPORT void JNICALL Java_com_impsapps_impsengine_common_multitouch_TouchListener_addTouchMoved(JNIEnv * env, jclass nativeClass, jlong touchId, jfloat pointX, jfloat pointY){
	IATouchHandler * touchHandler = IATouchManager_getTouchHandler((long) touchId);
	IATouchHandler_setTouchLocation(touchHandler, IAPoint_make((float) pointX, (float) pointY));
	touchHandlersTemp[currentLengthOfTouchHandlersTemp] = touchHandler;
	currentLengthOfTouchHandlersTemp++;
}

JNIEXPORT void JNICALL Java_com_impsapps_impsengine_common_multitouch_TouchListener_executeOnTouchMoved(JNIEnv * env, jclass nativeClass){
	IAJni_acquireApplicationEntrance(env);
	IATouchManager_onTouchMoved(currentLengthOfTouchHandlersTemp, touchHandlersTemp);
	IAJni_dispenseApplicationEntrance();
}

JNIEXPORT void JNICALL Java_com_impsapps_impsengine_common_multitouch_TouchListener_onTouchEnded(JNIEnv * env, jclass nativeClass, jlong touchId, jfloat pointX, jfloat pointY){
	IAJni_acquireApplicationEntrance(env);
	IATouchHandler * touchHandler = IATouchManager_getTouchHandler((long) touchId);
	IATouchHandler_setTouchLocation(touchHandler, IAPoint_make((float) pointX, (float) pointY));

	size_t lengthOfTouchHandlers = 1;
	IATouchHandler * touchHandlers[lengthOfTouchHandlers];
	touchHandlers[0] = touchHandler;
	IATouchManager_onTouchEnded(lengthOfTouchHandlers, touchHandlers);
	IAJni_dispenseApplicationEntrance();
}

JNIEXPORT void JNICALL Java_com_impsapps_impsengine_common_multitouch_TouchListener_destroyTouchHandler(JNIEnv * env, jclass nativeClass, jlong touchId){
	IATouchHandler * touchHandler = IATouchManager_getTouchHandler((long) touchId);
	IATouchManager_destroyTouchHandler(touchHandler);
}

void IATouchManagerHandler_terminateJni(JNIEnv * env){
	IA_free(touchHandlersTemp);
}


