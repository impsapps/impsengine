#include "IALibrary.h"
#include "IAOpenGLWinMappings.h"
#include "IABitmap+Native.h"

static IAOpenGLWinMappings mappings;

void IAOpenGLWinMappings_setMappings(IAOpenGLWinMappings mappingsTemp) {
	mappings = mappingsTemp;
}

void * IABitmap_nativeCreateRefFromAsset(const char * assetName) {
	return mappings.IABitmap_nativeCreateRefFromAsset(assetName);
}

void * IABitmap_nativeCreateRefFromScreen(int x, int y, int width, int height) {
	return mappings.IABitmap_nativeCreateRefFromScreen(x, y, width, height);
}

IASize IABitmap_nativeGetSourceSize(void * bitmapRef) {
	return mappings.IABitmap_nativeGetSourceSize(bitmapRef);
}

void IABitmap_nativeBind(void * bitmapRef) {
	mappings.IABitmap_nativeBind(bitmapRef);
}

void IABitmap_nativeDestroyBitmapRef(void * bitmapRef) {
	mappings.IABitmap_nativeDestroyBitmapRef(bitmapRef);
}

