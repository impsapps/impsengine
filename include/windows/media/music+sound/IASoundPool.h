//
//  SoundPool.h
//  MusicSound
//
//  Created by Konstantin Merker on 18/03/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IASoundPool_h
#define IASoundPool_h

void IASoundPool_commence(int maxNumberOfStreams);

int IASoundPool_add(const char * assetName);

void IASoundPool_play(int soundId);

void IASoundPool_terminate();

#endif
