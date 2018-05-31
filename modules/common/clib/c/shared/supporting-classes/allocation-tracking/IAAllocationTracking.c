//
//  IAAllocationTracking.c
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 25.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAAllocationTracking.h"
#include "IAAllocationTracking+Internal.h"
#include "IAAllocationTrackingEvent.h"
#include "IAAutoExpandingHashMap.h"
#include "IAAllocationTrackingElement.h"
#include "IAOperatingSystem.h"
#include "IACharArray.h"

#define CLASSNAME "IAAllocationTracking"

#ifdef DEBUG

#include "IARecursiveLock.h"
#include <stdlib.h>
#include <stdint.h>

static IAAutoExpandingHashMap * objectInformations;
static IAAllocationTrackingEvent * event;

IA_POSIX_ONLY(static IARecursiveLock * lock);

static bool volatile isCommenced = false;
static bool isTrackingEnabled = false;
static bool areCallbacksDisabled = false;

void IAAllocationTracking_commenceIfNeeded(void){
    if (isCommenced) {
        return;
    }
    IA_POSIX_ONLY(lock = IARecursiveLock_new());
    objectInformations = IAAutoExpandingHashMap_new();
    event = IAAllocationTrackingEvent_new();
    isCommenced = true;
    isTrackingEnabled = true;
    areCallbacksDisabled = false;
}

void IAAllocationTracking_register(IAAllocationTrackingDelegate * delegate){
    IA_POSIX_ONLY(IARecursiveLock_lock(lock));
    debugAssert(areCallbacksDisabled == false);
    debugAssert(isTrackingEnabled == true);
    isTrackingEnabled = false;
    IAAllocationTrackingEvent_register(event, delegate);
    isTrackingEnabled = true;
    IA_POSIX_ONLY(IARecursiveLock_unlock(lock));
}

void IAAllocationTracking_unregister(IAAllocationTrackingDelegate * delegate){
    IA_POSIX_ONLY(IARecursiveLock_lock(lock));
    debugAssert(areCallbacksDisabled == false);
    debugAssert(isTrackingEnabled == true);
    isTrackingEnabled = false;
    IAAllocationTrackingEvent_unregister(event, delegate);
    isTrackingEnabled = true;
    IA_POSIX_ONLY(IARecursiveLock_unlock(lock));
}

void IAAllocationTracking_objectAllocated(const void * object, size_t size, const char * className){
    if (isCommenced == false) {
        return;
    }
    IA_POSIX_ONLY(IARecursiveLock_lock(lock));
    if (isTrackingEnabled) {
        isTrackingEnabled = false;
        char objectKey[IA_KEY_SIZE_FOR_OBJECT];
        IAHashMap_getKeyForObject(object, objectKey);
        debugAssert(IAAutoExpandingHashMap_containsKey(objectInformations, objectKey) == false);
        IAAllocationTrackingElement * info = IAAllocationTrackingElement_new(size, className, areCallbacksDisabled);
        IAAutoExpandingHashMap_add(objectInformations, objectKey, info);
        isTrackingEnabled = true;
        if (areCallbacksDisabled == false) {
            areCallbacksDisabled = true;
            IAAllocationTrackingEvent_onObjectAllocated(event, object, size, className);
            areCallbacksDisabled = false;
        }
    }
    IA_POSIX_ONLY(IARecursiveLock_unlock(lock));
}

void IAAllocationTracking_objectReallocated(const void * object, size_t newSize){
    if (isCommenced == false) {
        return;
    }
    IA_POSIX_ONLY(IARecursiveLock_lock(lock));
    if (isTrackingEnabled) {
        isTrackingEnabled = false;
        char objectKey[IA_KEY_SIZE_FOR_OBJECT];
        IAHashMap_getKeyForObject(object, objectKey);
        IAAllocationTrackingElement * info = IAAutoExpandingHashMap_get(objectInformations, objectKey);
        debugAssert(info != NULL);
        size_t oldSize = IAAllocationTrackingElement_getSize(info);
        const char * className = IAAllocationTrackingElement_getClassName(info);
        IAAllocationTrackingElement_setSize(info, newSize);
        isTrackingEnabled = true;
        
        if (areCallbacksDisabled == false) {
            areCallbacksDisabled = true;
            IAAllocationTrackingEvent_onObjectReallocated(event, object, oldSize, newSize, className);
            areCallbacksDisabled = false;
        }
    }
    IA_POSIX_ONLY(IARecursiveLock_unlock(lock));
}

void IAAllocationTracking_objectDeallocated(const void * object){
    if (isCommenced == false) {
        return;
    }
    IA_POSIX_ONLY(IARecursiveLock_lock(lock));
    if (isTrackingEnabled) {
        isTrackingEnabled = false;
        char objectKey[IA_KEY_SIZE_FOR_OBJECT];
        IAHashMap_getKeyForObject(object, objectKey);
        IAAllocationTrackingElement * info = IAAutoExpandingHashMap_remove(objectInformations, objectKey);
        debugAssert(info != NULL);
        size_t size = IAAllocationTrackingElement_getSize(info);
        const char * className = IAAllocationTrackingElement_getClassName(info);
        isTrackingEnabled = true;
        
        if (IAAllocationTrackingElement_areCallbacksDisabled(info) == false) {
            IAAllocationTrackingEvent_onObjectDeallocated(event, object, size, className);
        }
        
        isTrackingEnabled = false;
        IAAllocationTrackingElement_release(info);
        isTrackingEnabled = true;
    }
    
    IA_POSIX_ONLY(IARecursiveLock_unlock(lock));
}

void IAAllocationTracking_increaseAllocationCount(const char * className){
    if (isCommenced == false) {
        return;
    }
    IA_POSIX_ONLY(IARecursiveLock_lock(lock));
    if (isTrackingEnabled && areCallbacksDisabled == false) {
        areCallbacksDisabled = true;
        IAAllocationTrackingEvent_onObjectAllocated(event, NULL, 0, className);
        areCallbacksDisabled = false;
    }
    IA_POSIX_ONLY(IARecursiveLock_unlock(lock));
}

void IAAllocationTracking_decreaseAllocationCount(const char * className){
    if (isCommenced == false) {
        return;
    }
    IA_POSIX_ONLY(IARecursiveLock_lock(lock));
    if (isTrackingEnabled && areCallbacksDisabled == false) {
        areCallbacksDisabled = true;
        IAAllocationTrackingEvent_onObjectDeallocated(event, NULL, 0, className);
        areCallbacksDisabled = false;
    }
    IA_POSIX_ONLY(IARecursiveLock_unlock(lock));
}

#endif
