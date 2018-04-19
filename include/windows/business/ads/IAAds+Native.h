//
//  IAAds+Native.h
//  Vungle
//
//  Created by Konstantin Merker on 02/08/17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAds_Native_h
#define IAAds_Native_h

#include "IAHashMap.h"

void IAAds_nativeCommence(const char * appId, size_t lengthOfPlacementIds, const char * placementIds[lengthOfPlacementIds]);

void IAAds_nativeTryToInitializeSDK();
void IAAds_notifyOnSDKInitializationSuccess();
void IAAds_notifyOnSDKInitializationFailure();

bool IAAds_nativeIsAdLoaded(const char * placementId);
void IAAds_nativeLoadAdAsync(const char * placementId);
void IAAds_nativeShowAd(const char * placementId);

void IAAds_notifyOnAdLoaded(const char * placementId);
void IAAds_notifyOnAdOpened(const char * placementId);
void IAAds_notifyOnAdClosed(const char * placementId, bool wasShownSuccessfully, bool didVisitShop);

void IAAds_nativeEnableLogging();
void IAAds_nativeDisableLogging();

void IAAds_nativeTerminate();

#endif
