//
//  IAPlayer.h
//  Hit Verto
//
//  Created by Konstantin Merker on 04.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAPlayer_h
#define Hit_Verto_IAPlayer_h

#include <stdbool.h>

bool IAPlayer_isAvailableOnPlatform();

void IAPlayer_setCorrespondingObject(void * correspondingObject);
void IAPlayer_setOnSignInFinishedFunction(void (*onSignInFinished)(void * object, bool wasSuccessful, bool signInDialogWasShown));

void IAPlayer_tryToSignInSilentlyIfPossible();
bool IAPlayer_isSignInDialogShown();

bool IAPlayer_isSignedIn();

#endif
