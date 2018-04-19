//
//  IAAds.h
//  Vungle
//
//  Created by Konstantin Merker on 28/12/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAds_h
#define IAAds_h

#include "IAAdDelegate.h"

/** \file IAAds.h
 * Note for Vungle on iOS: To use Vungle ads on iOS you have to link against the VungleSDK.framework version 5.1.0. Additionally, you have to force loading all classes from the vungle framework by adding to your project under "Build Settings" -> "Other Linker Flags" the value "-ObjC" or "-force_load [... path to Vungle SDK]/VungleSDK.framework/VungleSDK". See also the official Vungle sample app if you are facing problems.
 */

void IAAds_commence(const IAAdDelegate * adDelegate, const char * appId, size_t lengthOfPlacementIds, const char * placementIds[lengthOfPlacementIds]);
void IAAds_tryToInitializeSDK();

/**
 * Calling this function on auto-cached placements is not needed.
 */

void IAAds_loadAdAsync(const char * placementId);
bool IAAds_isAdLoaded(const char * placementId);
void IAAds_showAd(const char * placementId);

void IAAds_enableLogging();
void IAAds_disableLogging();

void IAAds_terminate();

#endif
