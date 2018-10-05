#include "IALibrary.h"
#include "IABitmap+Native.h"
#include "IABitmap.h"

#define CLASSNAME "IABitmap"


static void * IABitmap_createBitmapRefFromAsset(IABitmap * this){
    void * nativeBitmap = IABitmap_nativeCreateRefFromAsset(IAString_toCharArray(this->assetName));
    if (nativeBitmap == NULL) {
        logError("Could not load bitmap for file named \"%s\".", IAString_toCharArray(this->assetName));
        abort();
    }
    return nativeBitmap;
}

void IABitmap_initWithAsset(IABitmap * this, const char * assetName){
    *this = (IABitmap){
        .base = IAObject_make(this),
        .assetName = IAString_new(assetName),
        .createRef = IABitmap_createBitmapRefFromAsset,
        .bitmapRef = NULL
    };
    IA_incrementInitCount();
}

void IABitmap_initFromScreen(IABitmap * this, int x, int y, int width, int height){
    void * bitmapRef = IABitmap_nativeCreateRefFromScreen(x, y, width, height);
    IABitmap_initWithBitmapRefAndGivePermissionToRecycle(this, bitmapRef);
}

void IABitmap_initWithBitmapRefAndGivePermissionToRecycle(IABitmap * this, void * bitmapRef){
    *this = (IABitmap){
        .base = IAObject_make(this),
        .assetName = NULL,
        .createRef = NULL,
        .bitmapRef = bitmapRef
    };
    IA_incrementInitCount();
}

IASize IABitmap_getSize(IABitmap * this){
    IABitmap_createRefIfNeeded(this);
    return IABitmap_nativeGetSourceSize(this->bitmapRef);
}

void * IABitmap_getBitmapRef(const IABitmap * bitmap){
    return bitmap->bitmapRef;
}

void IABitmap_createRefIfNeeded(IABitmap * this){
    if (this->bitmapRef == NULL) {
        this->bitmapRef = this->createRef(this);
    }
}

void IABitmap_bind(IABitmap * this){
    IABitmap_nativeBind(this->bitmapRef);
#if IA_CURRENT_OPERATING_SYSTEM == IA_OPERATING_SYSTEM_IOS
    IABitmap_destroyRefIfPossible(this);
#endif
}

void IABitmap_destroyRefIfPossible(IABitmap * this){
    //We want to make sure that we can recreate the bitmap if we destroy it.
    if (this->bitmapRef != NULL && this->createRef != NULL) {
        IABitmap_nativeDestroyBitmapRef(this->bitmapRef);
        this->bitmapRef = NULL;
    }
}

void IABitmap_deinit(IABitmap * this){
    if (this->bitmapRef != NULL){
        IABitmap_nativeDestroyBitmapRef(this->bitmapRef);
    }
    if (this->assetName) {
        IAString_release(this->assetName);
    }
    IA_decrementInitCount();
}


