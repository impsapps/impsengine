//
//  IAAudioStream.h
//  MusicSound
//
//  Created by Konstantin Merker on 21/03/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAudioStream_h
#define IAAudioStream_h

typedef struct{
    void * data;
    //@get
    size_t numberOfAssets;
} IAAudioStream;


IAAudioStream IAAudioStream_new(size_t numberOfAssets, const char * assetNames[numberOfAssets]);

bool IAAudioStream_isPlaying(const IAAudioStream);

bool IAAudioStream_shouldAddNextItem(IAAudioStream);
void IAAudioStream_addNextItem(IAAudioStream, int indexOfAudioAsset);

void IAAudioStream_reset(IAAudioStream);

void IAAudioStream_release(IAAudioStream);

#endif
