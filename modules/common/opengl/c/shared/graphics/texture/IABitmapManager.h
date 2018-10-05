#ifndef IABitmapManager_h
#define IABitmapManager_h

#include "IABitmap.h"
#include "IAArrayList.h"

typedef struct{
    //@extend
    IAObject base;
    IAArrayList * bitmaps;
    IABitmap * lockedBitmap;
} IABitmapManager;


void IABitmapManager_init(IABitmapManager *);

void IABitmapManager_addBitmap(IABitmapManager *, IABitmap * bitmap);
void IABitmapManager_removeBitmap(IABitmapManager *, IABitmap * bitmap);

void IABitmapManager_lockBitmapRefFromBeeingDestroyed(IABitmapManager *, IABitmap * bitmap);
void IABitmapManager_unlockBitmapRefFromBeeingDestroyed(IABitmapManager *, IABitmap * bitmap);

void IABitmapManager_destroyBitmapRefs(IABitmapManager *);

void IABitmapManager_deinit(IABitmapManager *);

#include "IABitmapManager+Generated.h"

#endif
