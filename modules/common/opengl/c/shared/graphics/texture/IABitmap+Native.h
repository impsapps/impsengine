#ifndef IABitmap_Native_h
#define IABitmap_Native_h

#include "IABitmap.h"
#include "IASize.h"

void * IABitmap_nativeCreateRefFromAsset(const char * assetName);
void * IABitmap_nativeCreateRefFromScreen(int x, int y, int width, int height);
IASize IABitmap_nativeGetSourceSize(void * bitmapRef);
void IABitmap_nativeBind(void * bitmapRef);
void IABitmap_nativeDestroyBitmapRef(void * bitmapRef);

void * IABitmap_getBitmapRef(const IABitmap * bitmap);

#endif
