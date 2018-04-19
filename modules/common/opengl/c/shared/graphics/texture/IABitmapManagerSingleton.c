//
//  IABitmapManagerSingleton.c
//  OpenGL
//
//  Created by Konstantin Merker on 02/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IABitmapManagerSingleton.h"

#define CLASSNAME "IABitmapManagerSingleton"



static IABitmapManager * defaultBitmapManager;
static IANotificationDelegate notificationDelegate;

static void IABitmapManagerSingleton_onMemoryWarningFunction(void * object){
    IABitmapManager_destroyBitmapRefs(defaultBitmapManager);
}

IABitmapManager * IABitmapManagerSingleton_getDefaultBitmapManager(){
    if (defaultBitmapManager == NULL) {
        IA_disableAllocationTracking();
        defaultBitmapManager = IABitmapManager_new();
        IA_enableAllocationTracking();
        notificationDelegate = (IANotificationDelegate){
            .notify = (void (*)(void *)) IABitmapManagerSingleton_onMemoryWarningFunction
        };
        IALibrary_registerOnMemoryWarningNotification(&notificationDelegate);
    }
    return defaultBitmapManager;
}

