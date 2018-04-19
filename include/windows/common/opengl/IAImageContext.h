//
//  IAImageContext.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 10.05.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IAImageContext_h
#define ImpsEngineiOS_IAImageContext_h

#include "IAImage.h"
#include "IAAutoExpandingHashMap.h"
#include "IAArrayList.h"
#include "IABitmapManager.h"
#include "IAAtlasAssets.h"

typedef struct{
	IAAutoExpandingHashMap * images;
    IAArrayList * textures;
    IATextureDelegate textureDelegate;
    IASize sizeOfLastTexture;
    IABitmapManager * bitmapManager;
    IAArrayList bitmaps;
    IAString assetNameTemp;
} IAImageContext;


void IAImageContext_init(IAImageContext *, IABitmapManager * bitmapManager);

void IAImageContext_addAtlas(IAImageContext *, const char * assetName);
void IAImageContext_addAtlasAssets(IAImageContext *, IAAtlasAssets * assets);

IAImage * IAImageContext_getImage(IAImageContext *, const char * imageName);
const IAAutoExpandingHashMap * IAImageContext_getImages(IAImageContext *);

void IAImageContext_deinit(IAImageContext *);

#include "IAImageContext+Generated.h"

#endif
