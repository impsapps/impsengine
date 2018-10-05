#include "IAStorage+Native.h"

#include "JNIEnv+HelperMethods.h"
#include "IAJni.h"

#define CLASSNAME "IAStorage"

static jclass jStorageClass;
static jmethodID jGetPrivateDataDir;


void IAStorage_commenceIfNeeded(JNIEnv * env){
	jStorageClass = JNIEnv_createNativeClass(env, "com/impsapps/impsengine/common/inputoutput/Storage");
	jGetPrivateDataDir = (*env)->GetStaticMethodID(env, jStorageClass, "getPrivateDataDir", "()Ljava/lang/String;");
}

void IAStorage_nativeGetPrivateDataDir(IAString * privateDataDir){
	JNIEnv * env = IAJni_getJNIEnv();
	IAStorage_commenceIfNeeded(env);

	jstring jPrivateDataDir = (*env)->CallStaticObjectMethod(env, jStorageClass, jGetPrivateDataDir);

	const char * chars = JNIEnv_createUTFChars(env, jPrivateDataDir);
	IAString_set(privateDataDir, chars);
	JNIEnv_destroyUTFChars(env, jPrivateDataDir, chars);

	JNIEnv_destroyLocalRef(env, jPrivateDataDir);
}

