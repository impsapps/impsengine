//
//  IAAllocationTracker.c
//  CLib
//
//  Created by Konstantin Merker on 27.05.18.
//Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAAllocationTracker.h"

#define CLASSNAME "IAAllocationTracker"

#ifdef DEBUG

typedef struct{
    long allocationCount;
    size_t allocationSize;
} IAAllocationTrackerElement;


static IAAllocationTrackerElement * getMemoryContextElement(IAAllocationTracker * this, const char * className){
    IAAllocationTrackerElement * element = IAAutoExpandingHashMap_get(this->allocationSizePerClass, className);
    if (element == NULL) {
        element = IA_calloc(1, sizeof(IAAllocationTrackerElement));
        IAAutoExpandingHashMap_add(this->allocationSizePerClass, className, element);
    }
    return element;
}

static void onObjectAllocated(IAAllocationTracker * this, const void * allocatedObject, size_t size, const char * className){
    IAAllocationTrackerElement * element = getMemoryContextElement(this, className);
    element->allocationSize += size;
    element->allocationCount++;
}

static void onObjectReallocated(IAAllocationTracker * this, const void * allocatedObject, size_t oldSize, size_t newSize, const char * className){
    IAAllocationTrackerElement * element = getMemoryContextElement(this, className);
    debugAssert(element->allocationSize + newSize >= oldSize);
    element->allocationSize += newSize;
    element->allocationSize -= oldSize;
}

static void onObjectDeallocated(IAAllocationTracker * this, const void * deallocatedObject, size_t allocationSize, const char * className){
    IAAllocationTrackerElement * element = getMemoryContextElement(this, className);
    debugAssert(element->allocationSize >= allocationSize);
    element->allocationSize -= allocationSize;
    element->allocationCount--;
}


void IAAllocationTracker_init(IAAllocationTracker * this){
    this->allocationSizePerClass = IAAutoExpandingHashMap_new();
    this->trackingDelegate = (IAAllocationTrackingDelegate){
        .correspondingObject = this,
        .onObjectAllocated = (void (*)(void *, const void *, size_t, const char *)) onObjectAllocated,
        .onObjectReallocated = (void (*)(void *, const void *, size_t, size_t, const char *)) onObjectReallocated,
        .onObjectDeallocated = (void (*)(void *, const void *, size_t, const char *)) onObjectDeallocated,
    };
    IA_increaseAllocationCount();
}

long IAAllocationTracker_getAllocationCountForClass(IAAllocationTracker * this, const char * className){
    IAAllocationTrackerElement * element = IAAutoExpandingHashMap_get(this->allocationSizePerClass, className);
    if (element == NULL) {
        return 0;
    }else{
        return element->allocationCount;
    }
}

size_t IAAllocationTracker_getAllocationSizeForClass(IAAllocationTracker * this, const char * className){
    IAAllocationTrackerElement * element = IAAutoExpandingHashMap_get(this->allocationSizePerClass, className);
    if (element == NULL) {
        return 0;
    }else{
        return element->allocationSize;
    }
}

bool IAAllocationTracker_isAnythingAllocated(IAAllocationTracker * this){
    IAAllocationTrackerElement * element;
    foreach (element in autoExpandingHashMapValues(this->allocationSizePerClass)) {
        if (element->allocationCount != 0 || element->allocationSize > 0){
            return true;
        }
    }
    return false;
}

static void IAAllocationTracker_logMemoryLeak(IAAllocationTracker * this){
    logError("!!!Memory Leak!!!");
    char * key;
    foreach (key in autoExpandingHashMapKeys(this->allocationSizePerClass)) {
        IAAllocationTrackerElement * element = IAAutoExpandingHashMap_get(this->allocationSizePerClass, key);
        if (element->allocationCount > 0) {
            logError("%s with %ld allocated objects and a total size of %ld.", key, element->allocationCount, element->allocationSize);
        }else if (element->allocationCount < 0) {
            logError("%s with %ld overreleased objects and a total size of %ld.", key, element->allocationCount, element->allocationSize);
        }else if (element->allocationSize > 0){
            logError("%s with 0 allocated objects and a total size of %ld.", key, element->allocationSize);
        }
    }
}

void IAAllocationTracker_log(IAAllocationTracker * this){
    if (IAAllocationTracker_isAnythingAllocated(this)) {
        IAAllocationTracker_logMemoryLeak(this);
    }else{
        logInfo("Everything ok!");
    }
}

void IAAllocationTracker_assert(IAAllocationTracker * this){
    assert(IAAllocationTracker_isAnythingAllocated(this) == false && "Memory leaks detected!");
}

static void IAAllocationTracker_freeObject(void * object){
    IA_free(object);
}

void IAAllocationTracker_deinit(IAAllocationTracker * this){
    IAAutoExpandingHashMap_callFunctionOnAllObjects(this->allocationSizePerClass, IAAllocationTracker_freeObject);
    IAAutoExpandingHashMap_release(this->allocationSizePerClass);
    IA_decreaseAllocationCount();
}

#endif

