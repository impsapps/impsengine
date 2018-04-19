//
//  IAOpenGLWinMappings.h
//  OpenGL
//
//  Created by Konstantin Merker on 16.03.18.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAOpenGLWinMappings_h
#define IAOpenGLWinMappings_h

#include <stdint.h>
#include "IASize.h"

typedef struct {
	void *(*IABitmap_nativeCreateRefFromAsset)(const char * assetName);
	void *(*IABitmap_nativeCreateRefFromScreen)(int x, int y, int width, int height);
	IASize(*IABitmap_nativeGetSourceSize)(void * bitmapRef);
	void(*IABitmap_nativeBind)(void * bitmapRef);
	void(*IABitmap_nativeDestroyBitmapRef)(void * bitmapRef);
} IAOpenGLWinMappings;

void IAOpenGLWinMappings_setMappings(IAOpenGLWinMappings mappings);

#endif
