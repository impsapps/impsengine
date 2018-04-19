//
//  IALibrary.c
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 25.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IALibrary.h"
#include "IALibrary+SendOnMemoryWarningNotification.h"
#include "IANotificationEvent.h"
#include "IATime.h"

#define CLASSNAME "IALibrary"

static bool isLibraryCommenced;
static IANotificationEvent * event;

void IALibrary_commence(void){
    IATime_commence();
    isLibraryCommenced = true;
    event = IANotificationEvent_new();
#ifdef DEBUG
    IAAllocationTracker_commence();
#endif
}

static void IALibrary_checkIfLibraryIsCommenced(void){
    assert(isLibraryCommenced && "IALibrary is not commenced!");
}

void IALibrary_registerOnMemoryWarningNotification(IANotificationDelegate * delegate){
    IALibrary_checkIfLibraryIsCommenced();
    IANotificationEvent_register(event, delegate);
}

void IALibrary_unregisterOnMemoryWarningNotification(IANotificationDelegate * delegate){
    IALibrary_checkIfLibraryIsCommenced();
    IANotificationEvent_unregister(event, delegate);
}

void IALibrary_onMemoryWarning(void){
    IANotificationEvent_notify(event);
}

#ifdef DEBUG

void * IALibrary_malloc(size_t size, const char * className){
    IALibrary_checkIfLibraryIsCommenced();
    IAAllocationTracker_objectAllocated(className);
    void * object = malloc(size);
    while (object == NULL) {
        IANotificationEvent_notify(event);
        object = malloc(size);
    }
    return object;
}

void * IALibrary_calloc(size_t count, size_t size, const char * className){
    IALibrary_checkIfLibraryIsCommenced();
    IAAllocationTracker_objectAllocated(className);
    void* object = calloc(count, size);
    while (object == NULL) {
        IANotificationEvent_notify(event);
        object = calloc(count, size);
    }
    return object;
}

void IALibrary_free(void* object, const char * className){
    IALibrary_checkIfLibraryIsCommenced();
    free(object);
    IAAllocationTracker_objectDeallocated(className);
}

#else

void * IALibrary_malloc(size_t size){
    void* object = malloc(size);
    while (object == NULL) {
        IANotificationEvent_notify(event);
        object = malloc(size);
    }
    return object;
}

void * IALibrary_calloc(size_t count, size_t size){
    void* object = calloc(count, size);
    while (object == NULL) {
        IANotificationEvent_notify(event);
        object = calloc(count, size);
    }
    return object;
}

void IALibrary_free(void* object){
    free(object);
}

#endif

void * IALibrary_realloc(void * object, size_t size){
#ifdef DEBUG
    IALibrary_checkIfLibraryIsCommenced();
#endif
    void* newObject = realloc(object, size);
    while (newObject == NULL) {
        IANotificationEvent_notify(event);
        newObject = realloc(object, size);
    }
    return newObject;
}

bool IALibrary_isDebugMode(void){
#ifdef DEBUG
    return true;
#else
    return false;
#endif
}

void IALibrary_terminate(void){
#ifdef DEBUG
    IAAllocationTracker_terminate();
#endif
    isLibraryCommenced = false;
}



