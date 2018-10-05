#include "com_impsapps_impsengine_common_openglrenderer_BaseActivity.h"
#include "com_impsapps_impsengine_common_openglrenderer_IASurfaceRenderer.h"

#include "IALibrary.h"
#include "IAAppHandler.h"
#include "IAAppHandler+Native.h"
#include "IAJni.h"
#include "IAAndroidLib+Jni.h"
#include "IATouchManagerHandler+Jni.h"
#include "IABitmap+Jni.h"
#include "IALock.h"

#define CLASSNAME "IAJniWrapper"


JNIEXPORT void JNICALL Java_com_impsapps_impsengine_common_openglrenderer_BaseActivity_nativeOnCreate(JNIEnv * env, jclass nativeClass){
	IALibrary_commenceIfNeeded();

	IAJni_commence(env);

	IAJni_acquireApplicationEntrance(env);
	IAAndroidLib_commenceJni(env);
	IATouchManagerHandler_commenceJni(env);
	IABitmap_commenceJni(env);

	IAAppHandler_onAppStart();
	IAJni_dispenseApplicationEntrance();
}

JNIEXPORT void JNICALL Java_com_impsapps_impsengine_common_openglrenderer_IASurfaceRenderer_onSurfaceCreated(JNIEnv * env, jclass nativeClass){
	IAJni_acquireApplicationEntrance(env);
	IAAppHandler_onSurfaceCreated();
	IAJni_dispenseApplicationEntrance();
}

JNIEXPORT void JNICALL Java_com_impsapps_impsengine_common_openglrenderer_IASurfaceRenderer_onSurfaceChanged(JNIEnv * env, jclass nativeClass, jint width, jint height){
	IAJni_acquireApplicationEntrance(env);
	IAAppHandler_onSurfaceChanged(IASize_make(width, height));
	IAJni_dispenseApplicationEntrance();
}

JNIEXPORT void JNICALL Java_com_impsapps_impsengine_common_openglrenderer_IASurfaceRenderer_onDrawFrame(JNIEnv * env, jclass nativeClass){
	IAJni_acquireApplicationEntrance(env);
	IAAppHandler_render();
	IAJni_dispenseApplicationEntrance();
}

JNIEXPORT void JNICALL Java_com_impsapps_impsengine_common_openglrenderer_BaseActivity_nativeSwitchToPausescreen(JNIEnv * env, jclass nativeClass){
    IAJni_acquireApplicationEntrance(env);
    bool shouldRenderPauseScreen;
    IAAppHandler_switchToPausescreen(&shouldRenderPauseScreen);
    IAJni_dispenseApplicationEntrance();
}

JNIEXPORT void JNICALL Java_com_impsapps_impsengine_common_openglrenderer_BaseActivity_nativeSaveGamestate(JNIEnv * env, jclass nativeClass){
    IAJni_acquireApplicationEntrance(env);
    IAAppHandler_saveGameState();
    IAJni_dispenseApplicationEntrance();
}

JNIEXPORT void JNICALL Java_com_impsapps_impsengine_common_openglrenderer_BaseActivity_nativeDestroyResources(JNIEnv * env, jclass nativeClass){
	IAJni_acquireApplicationEntrance(env);

	IAAppHandler_destroyResources();

	IATouchManagerHandler_terminateJni(env);
	IABitmap_terminateJni(env);
	IAAndroidLib_terminateJni(env);

	IAJni_dispenseApplicationEntrance();
	IAJni_terminate();

#if DEBUG == true
	IAAllocationTracker_log();
#endif
}

