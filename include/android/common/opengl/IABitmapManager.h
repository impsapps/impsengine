//
//  IABitmapManager.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 06.06.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IABitmapManager_h
#define ImpsEngineiOS_IABitmapManager_h

#include "IABitmap.h"
#include "IAArrayList.h"

typedef struct{
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
