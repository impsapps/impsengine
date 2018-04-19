//
//  SoundPool+Native.h
//  MusicSound
//
//  Created by Konstantin Merker on 19/03/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IASoundPool_Native_h
#define IASoundPool_Native_h

void * IASoundPool_nativeCreate(int maxNumberOfStreams);

int IASoundPool_nativeAdd(void * nativePool, const char * assetName);
void IASoundPool_nativePlay(void * nativePool, int soundId);

void IASoundPool_nativeDestroy(void * nativePool);

#endif
