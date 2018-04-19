//
//  IABitmapManager.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 06.06.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IABitmapManager.h"

#define CLASSNAME "IABitmapManager"



void IABitmapManager_init(IABitmapManager * this){
    this->bitmaps = IAArrayList_new(10);
    this->lockedBitmap = NULL;
}

void IABitmapManager_addBitmap(IABitmapManager * this, IABitmap * bitmap){
    IAArrayList_add(this->bitmaps, bitmap);
}

void IABitmapManager_removeBitmap(IABitmapManager * this, IABitmap * bitmap){
    IAArrayList_removeObject(this->bitmaps, bitmap);
}

void IABitmapManager_lockBitmapRefFromBeeingDestroyed(IABitmapManager * this, IABitmap * bitmap){
    assert(this->lockedBitmap == NULL && "Locking of multiple bitmaps is not implemented yet!");
    this->lockedBitmap = bitmap;
}

void IABitmapManager_unlockBitmapRefFromBeeingDestroyed(IABitmapManager * this, IABitmap * bitmap){
    assert(this->lockedBitmap == bitmap && "Bitmap was not locked!");
    this->lockedBitmap = NULL;
}

void IABitmapManager_destroyBitmapRefs(IABitmapManager * this){
    IABitmap * bitmap;
    foreach (bitmap in arrayList(this->bitmaps)){
        if (bitmap != this->lockedBitmap) {
            IABitmap_destroyRefIfPossible(bitmap);
        }
    }
}

void IABitmapManager_deinit(IABitmapManager * this){
    IAArrayList_release(this->bitmaps);
}


