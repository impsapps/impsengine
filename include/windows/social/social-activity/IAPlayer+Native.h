//
//  IAPlayer+Native.h
//  Hit Verto
//
//  Created by Konstantin Merker on 10.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAPlayer_Native_h
#define Hit_Verto_IAPlayer_Native_h

#include <stdbool.h>

bool IAPlayer_nativeIsAvailableOnPlatform();

void IAPlayer_nativeTryToSignInSilentlyIfPossible();

bool IAPlayer_nativeIsSignedIn();

void IAPlayer_notifyOnSignInDialogShown();
void IAPlayer_notifyOnSignInFinished(bool wasSuccessful);

#endif
