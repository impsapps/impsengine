//
//  IALibrary.c
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 25.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IALibrary.h"
#include "IALibrary+SendOnMemoryWarningNotification.h"
#include "IAAllocationTracking+Internal.h"
#include "IANotificationEvent.h"
#include "IATime.h"

#define CLASSNAME "IALibrary"

static bool isLibraryCommenced;
static IANotificationEvent * memoryWarningEvent;

void IALibrary_commenceIfNeeded(void){
    isLibraryCommenced = true;
    IATime_commenceIfNeeded();
    memoryWarningEvent = IANotificationEvent_new();
#ifdef DEBUG
    IAAllocationTracking_commenceIfNeeded();
#endif
}

static void IALibrary_checkIfLibraryIsCommenced(void){
    assert(isLibraryCommenced && "IALibrary is not commenced!");
}

void IALibrary_registerOnMemoryWarningNotification(IANotificationDelegate * delegate){
    IALibrary_checkIfLibraryIsCommenced();
    IANotificationEvent_register(memoryWarningEvent, delegate);
}

void IALibrary_unregisterOnMemoryWarningNotification(IANotificationDelegate * delegate){
    IALibrary_checkIfLibraryIsCommenced();
    IANotificationEvent_unregister(memoryWarningEvent, delegate);
}

void IALibrary_onMemoryWarning(void){
    IANotificationEvent_notify(memoryWarningEvent);
}

#ifdef DEBUG

void * IALibrary_malloc(size_t size, const char * className){
    IALibrary_checkIfLibraryIsCommenced();
    void * object = malloc(size);
    while (object == NULL) {
        IANotificationEvent_notify(memoryWarningEvent);
        object = malloc(size);
    }
    IAAllocationTracking_objectAllocated(object, size, className);
    return object;
}

void * IALibrary_calloc(size_t count, size_t size, const char * className){
    IALibrary_checkIfLibraryIsCommenced();
    void* object = calloc(count, size);
    while (object == NULL) {
        IANotificationEvent_notify(memoryWarningEvent);
        object = calloc(count, size);
    }
    IAAllocationTracking_objectAllocated(object, size, className);
    return object;
}

void * IALibrary_realloc(void * object, size_t size, const char * className){
    IALibrary_checkIfLibraryIsCommenced();
    void* newObject = realloc(object, size);
    while (newObject == NULL) {
        IANotificationEvent_notify(memoryWarningEvent);
        newObject = realloc(object, size);
    }
    if (newObject != object) {
        IAAllocationTracking_objectDeallocated(object);
        IAAllocationTracking_objectAllocated(newObject, size, className);
    }else{
        IAAllocationTracking_objectReallocated(newObject, size);
    }
    return newObject;
}

void IALibrary_free(void* object, const char * className){
    IALibrary_checkIfLibraryIsCommenced();
    free(object);
    IAAllocationTracking_objectDeallocated(object);
}

#else

void * IALibrary_malloc(size_t size){
    void* object = malloc(size);
    while (object == NULL) {
        IANotificationEvent_notify(memoryWarningEvent);
        object = malloc(size);
    }
    return object;
}

void * IALibrary_calloc(size_t count, size_t size){
    void* object = calloc(count, size);
    while (object == NULL) {
        IANotificationEvent_notify(memoryWarningEvent);
        object = calloc(count, size);
    }
    return object;
}

void * IALibrary_realloc(void * object, size_t size){
    void* newObject = realloc(object, size);
    while (newObject == NULL) {
        IANotificationEvent_notify(memoryWarningEvent);
        newObject = realloc(object, size);
    }
    return newObject;
}

void IALibrary_free(void* object){
    free(object);
}

#endif

bool IALibrary_isDebugMode(void){
#ifdef DEBUG
    return true;
#else
    return false;
#endif
}

