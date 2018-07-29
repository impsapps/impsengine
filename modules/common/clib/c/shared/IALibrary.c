//
//  IALibrary.c
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 25.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IALibrary.h"
#include "IALibrary+SendOnMemoryWarningNotification.h"
#include "IAAutoreleasePool+Internal.h"
#include "IAAllocationTracking+Internal.h"
#include "IANotificationEvent.h"
#include "IATime.h"

#define CLASSNAME "IALibrary"

#define OBJECT_IDENTIFIER 871829345L

typedef struct{
#ifdef DEBUG
    long objectIdentifier;
#endif
    long allocationCount;
    void (*deinit)(void * object);
} IAObjectInformation;

static bool isLibraryCommenced;
static IANotificationEvent * memoryWarningEvent;

void IALibrary_commenceIfNeeded(void){
    if (isLibraryCommenced) {
        return;
    }
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
    IAAutoreleasePool_incrementShouldReleaseImmediatlyCount();
    IANotificationEvent_notify(memoryWarningEvent);
    IAAutoreleasePool_decrementShouldReleaseImmediatlyCount();
}

#ifdef DEBUG

static IAObjectInformation * getObjectInformation(void * pointer){
    IAObjectInformation * information = pointer;
    information -= 1;
    return information;
}

static bool isObjectPointer(void * pointer){
    IAObjectInformation * information = getObjectInformation(pointer);
    return information->objectIdentifier == OBJECT_IDENTIFIER;
}

void * IALibrary_new(size_t size, void (*deinit)(void * object), const char * className){
    IALibrary_checkIfLibraryIsCommenced();
    IAObjectInformation * information = malloc(size + sizeof(IAObjectInformation));
    while (information == NULL) {
        IALibrary_onMemoryWarning();
        information = malloc(size + sizeof(IAObjectInformation));
    }
    *information = (IAObjectInformation){
        .objectIdentifier = OBJECT_IDENTIFIER,
        .allocationCount = 1,
        .deinit = deinit
    };
    void * object = information + 1;
    IAAllocationTracking_objectAllocated(object, size, className);
    return object;
}

void IALibrary_retain(void * object){
    IALibrary_checkIfLibraryIsCommenced();
    object = *(void **)object;
    debugAssert(isObjectPointer(object) && "Cannot retain non object.");
    IAObjectInformation * information = getObjectInformation(object);
    debugAssert(information->allocationCount > 0 && "Cannot retain an object which already has been deinitialized.");
    information->allocationCount++;
}

void IALibrary_autorelease(void * object){
    IALibrary_checkIfLibraryIsCommenced();
    IAAutoreleasePool_add(object);
}

void IALibrary_release(void * object){
    IALibrary_checkIfLibraryIsCommenced();
    object = *(void **)object;
    debugAssert(isObjectPointer(object) && "Cannot release non object.");
    IAObjectInformation * information = getObjectInformation(object);
    debugAssert(information->allocationCount > 0 && "Cannot release an object which already has been deinitialized.");
    information->allocationCount--;
    if (information->allocationCount == 0){
        if (information->deinit) {
            IAAutoreleasePool_incrementShouldReleaseImmediatlyCount();
            information->deinit(object);
            IAAutoreleasePool_decrementShouldReleaseImmediatlyCount();
        }
        free(information);
        IAAllocationTracking_objectDeallocated(object);
    }
}

void * IALibrary_malloc(size_t size, const char * className){
    IALibrary_checkIfLibraryIsCommenced();
    void * object = malloc(size);
    while (object == NULL) {
        IALibrary_onMemoryWarning();
        object = malloc(size);
    }
    IAAllocationTracking_dataAllocated(object, size, className);
    return object;
}

void * IALibrary_calloc(size_t count, size_t size, const char * className){
    IALibrary_checkIfLibraryIsCommenced();
    void* object = calloc(count, size);
    while (object == NULL) {
        IALibrary_onMemoryWarning();
        object = calloc(count, size);
    }
    IAAllocationTracking_dataAllocated(object, size, className);
    return object;
}

void * IALibrary_realloc(void * object, size_t size, const char * className){
    IALibrary_checkIfLibraryIsCommenced();
    void* newObject = realloc(object, size);
    while (newObject == NULL) {
        IALibrary_onMemoryWarning();
        newObject = realloc(object, size);
    }
    IAAllocationTracking_dataReallocated(object, newObject, size);
    return newObject;
}

void IALibrary_free(void * object, const char * className){
    IALibrary_checkIfLibraryIsCommenced();
    free(object);
    IAAllocationTracking_dataDeallocated(object);
}

#else

void * IALibrary_new(size_t size, void (*deinit)(void * object), const char * className){
    IAObjectInformation * information = malloc(size + sizeof(IAObjectInformation));
    while (information == NULL) {
        IALibrary_onMemoryWarning();
        information = malloc(size + sizeof(IAObjectInformation));
    }
    *information = (IAObjectInformation){
        .allocationCount = 1,
        .deinit = deinit
    };
    void * object = information + 1;
    return object;
}

void IALibrary_retain(void * object, const char * className){
    IAObjectInformation * information = object;
    information -= 1;
    information->allocationCount++;
}

void IALibrary_autorelease(void * object){
    IAAutoreleasePool_add(object, IALibrary_release);
}

void IALibrary_release(void * object, const char * className){
    IAObjectInformation * information = object;
    information -= 1;
    information->allocationCount--;
    if (information->allocationCount == 0){
        if (information->deinit) {
            IAAutoreleasePool_incrementShouldReleaseImmediatlyCount();
            information->deinit(object);
            IAAutoreleasePool_decrementShouldReleaseImmediatlyCount();
        }
        free(information);
    }
}

void * IALibrary_malloc(size_t size){
    void* object = malloc(size);
    while (object == NULL) {
        IALibrary_onMemoryWarning();
        object = malloc(size);
    }
    return object;
}

void * IALibrary_calloc(size_t count, size_t size){
    void* object = calloc(count, size);
    while (object == NULL) {
        IALibrary_onMemoryWarning();
        object = calloc(count, size);
    }
    return object;
}

void * IALibrary_realloc(void * object, size_t size){
    void* newObject = realloc(object, size);
    while (newObject == NULL) {
        IALibrary_onMemoryWarning();
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

