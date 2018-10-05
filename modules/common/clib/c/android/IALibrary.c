#include "IALibrary.h"
#include "IALibrary+SendOnMemoryWarningNotification.h"
#include "com_impsapps_impsengine_common_clib_Library.h"
#include "IAJni.h"

#include "JNIEnv+HelperMethods.h"

#define CLASSNAME "IALibrary"


JNIEXPORT void JNICALL Java_com_impsapps_impsengine_common_clib_Library_onMemoryWarning(JNIEnv * env, jclass nativeClass){
    IAJni_acquireApplicationEntrance(env);
    IALibrary_onMemoryWarning();
    IAJni_dispenseApplicationEntrance();
}

JNIEXPORT jboolean JNICALL Java_com_impsapps_impsengine_common_clib_Library_isDebugMode(JNIEnv* env, jclass nativeClass){
    return IALibrary_isDebugMode();
}

