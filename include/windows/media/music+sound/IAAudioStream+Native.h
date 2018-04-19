//
//  IAAudioStream+Native.h
//  MusicSound
//
//  Created by Konstantin on 11.06.17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAudioStream_Native_h
#define IAAudioStream_Native_h

#include <stddef.h>
#include <stdbool.h>

void * IAAudioStream_nativeCreate(size_t numberOfAssets, const char * assetNames[numberOfAssets]);

bool IAAudioStream_nativeIsPlaying(void * nativeAudioStream);

bool IAAudioStream_nativeShouldAddNextItem(const void * nativeAudioStream);
void IAAudioStream_nativeAddNextItem(void * nativeAudioStream, int indexOfAudioAsset);

void IAAudioStream_nativeReset(void * nativeAudioStream);

void IAAudioStream_nativeDestroy(void * nativeAudioStream);

#endif
