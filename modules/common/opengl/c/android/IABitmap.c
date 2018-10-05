#include "IANativeObject.h"
#include "IABitmap+Jni.h"
#include "IABitmap+Native.h"
#include "JNIEnv+HelperMethods.h"

static jclass jBitmapClass;
static jmethodID jGetWidth;
static jmethodID jGetHeight;
static jmethodID jRecycle;

static jclass jBitmapHelperClass;
static jmethodID jCreateBitmapFromAsset;
static jmethodID jCreateBitmapFromScreen;
static jmethodID jBind;


void IABitmap_commenceJni(JNIEnv * env){
	jclass jBitmapClass = JNIEnv_createNativeClass(env, "android/graphics/Bitmap");
	jGetWidth = (*env)->GetMethodID(env, jBitmapClass, "getWidth", "()I");
	jGetHeight = (*env)->GetMethodID(env, jBitmapClass, "getHeight", "()I");
	jRecycle = (*env)->GetMethodID(env, jBitmapClass, "recycle", "()V");

	jBitmapHelperClass = JNIEnv_createNativeClass(env, "com/impsapps/impsengine/common/opengl/BitmapHelper");
    jCreateBitmapFromAsset = (*env)->GetStaticMethodID(env, jBitmapHelperClass, "createBitmapFromAsset", "(Ljava/lang/String;)Landroid/graphics/Bitmap;");
	jCreateBitmapFromScreen = (*env)->GetStaticMethodID(env, jBitmapHelperClass, "createBitmapFromScreen", "(IIII)Landroid/graphics/Bitmap;");
	jBind = (*env)->GetStaticMethodID(env, jBitmapHelperClass, "bind", "(Landroid/graphics/Bitmap;)V");
}

void * IABitmap_nativeCreateRefFromAsset(const char * assetName){
	JNIEnv * env = IAJni_getJNIEnv();
	jstring jAssetName = JNIEnv_createStringWithUTFCharsLocally(env, assetName);
	jobject jBitmap = (*env)->CallStaticObjectMethod(env, jBitmapHelperClass, jCreateBitmapFromAsset, jAssetName);
	JNIEnv_destroyStringWithUTFCharsLocally(env, jAssetName);
	if (jBitmap != NULL){
        IANativeObject * nativeBitmap = IANativeObject_new(env, jBitmap);
        (*env)->DeleteLocalRef(env, jBitmap);
        return (void *) nativeBitmap;
	}else{
        return NULL;
    }
}

void * IABitmap_nativeCreateRefFromScreen(int x, int y, int width, int height){
	JNIEnv * env = IAJni_getJNIEnv();
	jobject jBitmap = (*env)->CallStaticObjectMethod(env, jBitmapHelperClass, jCreateBitmapFromScreen, x, y, width, height);
	IANativeObject * nativeBitmap = IANativeObject_new(env, jBitmap);
	(*env)->DeleteLocalRef(env, jBitmap);
	return (void *) nativeBitmap;
}

IASize IABitmap_nativeGetSourceSize(void * bitmapReference){
	JNIEnv * env = IAJni_getJNIEnv();
	IANativeObject * nativeObject = (IANativeObject *) bitmapReference;
	jobject jBitmap = IANativeObject_getJObject(nativeObject);
	jint jWidth = (*env)->CallIntMethod(env, jBitmap, jGetWidth);
	jint jHeight = (*env)->CallIntMethod(env, jBitmap, jGetHeight);
	return IASize_make(jWidth, jHeight);
}

void IABitmap_nativeBind(void * bitmapReference){
	JNIEnv * env = IAJni_getJNIEnv();
	IANativeObject * nativeBitmap = (IANativeObject *) bitmapReference;
	jobject jIABitmap = IANativeObject_getJObject(nativeBitmap);
	(*env)->CallStaticVoidMethod(env, jBitmapHelperClass, jBind, jIABitmap);
}

void IABitmap_nativeDestroyBitmapRef(void * bitmapReference){
	JNIEnv * env = IAJni_getJNIEnv();
	IANativeObject * nativeBitmap = (IANativeObject *) bitmapReference;
	jobject jBitmap = IANativeObject_getJObject(nativeBitmap);
	(*env)->CallVoidMethod(env, jBitmap, jRecycle);
	IANativeObject_release(nativeBitmap, env);
}

void IABitmap_terminateJni(JNIEnv * env){
	JNIEnv_destroyNativeClass(env, jBitmapClass);
	JNIEnv_destroyNativeClass(env, jBitmapHelperClass);
}

