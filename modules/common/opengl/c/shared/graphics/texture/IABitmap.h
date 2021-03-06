#ifndef IABitmap_h
#define IABitmap_h

#include "IAString.h"
#include "IASize.h"

typedef struct IABitmap IABitmap;

struct IABitmap{
    //@extend
    IAObject base;
    IAString * assetName;
    void * (*createRef)(IABitmap *);
    void * bitmapRef;
};


void IABitmap_initWithAsset(IABitmap *, const char * assetName);
void IABitmap_initFromScreen(IABitmap *, int x, int y, int width, int height);
void IABitmap_initWithBitmapRefAndGivePermissionToRecycle(IABitmap *, void * bitmapRef);

IASize IABitmap_getSize(IABitmap * this);

void IABitmap_createRefIfNeeded(IABitmap *);

void IABitmap_bind(IABitmap *);

void IABitmap_destroyRefIfPossible(IABitmap *);

void IABitmap_deinit(IABitmap *);

#include "IABitmap+Generated.h"

#endif
