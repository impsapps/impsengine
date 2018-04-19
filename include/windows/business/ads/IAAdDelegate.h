//
//  IAAdDelegate.h
//  Vungle
//
//  Created by Konstantin Merker on 28/12/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAdDelegate_h
#define IAAdDelegate_h

#include <stddef.h>
#include <stdbool.h>

typedef struct{
    void (*onAdLoaded)(const char * placementId);
    void (*onAdOpened)(const char * placementId);
    void (*onAdClosed)(const char * placementId, bool wasSuccessfulShown, bool didVisitShop);
} IAAdDelegate;

static inline void IAAdDelegate_onAdLoaded(const IAAdDelegate * adDelegate, const char * placementId){
    if (adDelegate->onAdLoaded != NULL) {
        adDelegate->onAdLoaded(placementId);
    }
}

static inline void IAAdDelegate_onAdOpened(const IAAdDelegate * adDelegate, const char * placementId){
    if (adDelegate->onAdOpened != NULL) {
        adDelegate->onAdOpened(placementId);
    }
}

static inline void IAAdDelegate_onAdClosed(const IAAdDelegate * adDelegate, const char * placementId, bool wasShownSuccessfully, bool didVisitShop){
    if (adDelegate->onAdClosed != NULL) {
        adDelegate->onAdClosed(placementId, wasShownSuccessfully, didVisitShop);
    }
}


#endif
