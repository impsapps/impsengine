//
//  IAAllocationTracker.c
//  CLib
//
//  Created by Konstantin Merker on 27.05.18.
//Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAAllocationTracker.h"
#include "IAAllocationTrackerElement.h"
#include "IAAllocationTracking.h"

#define CLASSNAME "IAAllocationTracker"

#ifdef DEBUG

static IAAllocationTrackerElement * getMemoryContextElement(IAAutoExpandingHashMap * elements, const char * className){
    IAAllocationTrackerElement * element = IAAutoExpandingHashMap_get(elements, className);
    if (element == NULL) {
        element = IAAllocationTrackerElement_new();
        IAAutoExpandingHashMap_add(elements, className, element);
        IAAllocationTrackerElement_release(element);
    }
    return element;
}

static void onObjectAllocated(IAAllocationTracker * this, const void * allocatedObject, size_t allocationSize, const char * className){
    IAAllocationTrackerElement * element = getMemoryContextElement(this->allocatedObjectsPerClass, className);
    IAAllocationTrackerElement_onAllocated(element, allocationSize);
}

static void onObjectDeallocated(IAAllocationTracker * this, const void * deallocatedObject, size_t allocationSize, const char * className){
    IAAllocationTrackerElement * element = getMemoryContextElement(this->allocatedObjectsPerClass, className);
    IAAllocationTrackerElement_onDeallocated(element, allocationSize);
}

static void onDataAllocated(IAAllocationTracker * this, const void * dataPointer, size_t size, const char * className){
    IAAllocationTrackerElement * element = getMemoryContextElement(this->allocatedDataPerClass, className);
    IAAllocationTrackerElement_onAllocated(element, size);
}

static void onDataReallocated(IAAllocationTracker * this, const void * oldDataPointer, const void * newDataPointer, size_t newSize, size_t oldSize, const char * className){
    IAAllocationTrackerElement * element = getMemoryContextElement(this->allocatedDataPerClass, className);
    IAAllocationTrackerElement_onReallocated(element, newSize, oldSize);
}

static void onDataDeallocated(IAAllocationTracker * this, const void * dataPointer, size_t size, const char * className){
    IAAllocationTrackerElement * element = getMemoryContextElement(this->allocatedDataPerClass, className);
    IAAllocationTrackerElement_onDeallocated(element, size);
}

static void onInitCountIncremented(IAAllocationTracker * this, const char * className){
    IAAllocationTrackerElement * element = getMemoryContextElement(this->initCountPerClass, className);
    IAAllocationTrackerElement_incrementAllocationCount(element);
}

static void onInitCountDecremented(IAAllocationTracker * this, const char * className){
    IAAllocationTrackerElement * element = getMemoryContextElement(this->initCountPerClass, className);
    IAAllocationTrackerElement_decrementAllocationCount(element);
}

void IAAllocationTracker_init(IAAllocationTracker * this){
    this->base = IAObject_make(this);
    this->allocatedObjectsPerClass = IAAutoExpandingHashMap_new();
    this->allocatedDataPerClass = IAAutoExpandingHashMap_new();
    this->initCountPerClass = IAAutoExpandingHashMap_new();
    this->trackingDelegate = (IAAllocationTrackingDelegate){
        .correspondingObject = this,
        .onObjectAllocated = (void (*)(void *, const void *, size_t, const char *)) onObjectAllocated,
        .onObjectDeallocated = (void (*)(void *, const void *, size_t, const char *)) onObjectDeallocated,
        .onDataAllocated = (void (*)(void *, const void *, size_t, const char *)) onDataAllocated,
        .onDataReallocated = (void (*)(void *, const void *, const void *, size_t, size_t, const char *)) onDataReallocated,
        .onDataDeallocated = (void (*)(void *, const void *, size_t, const char *)) onDataDeallocated,
        .onInitCountIncremented = (void (*)(void *, const char *)) onInitCountIncremented,
        .onInitCountDecremented = (void (*)(void *, const char *)) onInitCountDecremented
    };
    IA_incrementInitCount();
}

void IAAllocationTracker_start(IAAllocationTracker * this){
    IAAllocationTracking_register(&this->trackingDelegate);
}

void IAAllocationTracker_stop(IAAllocationTracker * this){
    IAAllocationTracking_unregister(&this->trackingDelegate);
}

long IAAllocationTracker_getAllocationCountForClass(IAAllocationTracker * this, const char * className){
    IAAllocationTrackerElement * element = IAAutoExpandingHashMap_get(this->allocatedObjectsPerClass, className);
    if (element == NULL) {
        return 0;
    }else{
        return element->allocationCount;
    }
}

size_t IAAllocationTracker_getAllocationSizeForClass(IAAllocationTracker * this, const char * className){
    IAAllocationTrackerElement * element = IAAutoExpandingHashMap_get(this->allocatedObjectsPerClass, className);
    if (element == NULL) {
        return 0;
    }else{
        return IAAllocationTrackerElement_getPositiveAllocationSize(element);
    }
}

bool IAAllocationTracker_isAnythingAllocated(IAAllocationTracker * this){
    IAAllocationTrackerElement * element;
    foreach (element in autoExpandingHashMapValues(this->allocatedObjectsPerClass)) {
        if (IAAllocationTrackerElement_getAllocationCount(element) != 0
            || IAAllocationTrackerElement_getPositiveAllocationSize(element) != 0
            || IAAllocationTrackerElement_getNegativeAllocationSize(element) != 0){
            return true;
        }
    }
    foreach (element in autoExpandingHashMapValues(this->allocatedObjectsPerClass)) {
        if (IAAllocationTrackerElement_getAllocationCount(element) != 0
            || IAAllocationTrackerElement_getPositiveAllocationSize(element) != 0
            || IAAllocationTrackerElement_getNegativeAllocationSize(element) != 0){
            return true;
        }
    }
    foreach (element in autoExpandingHashMapValues(this->initCountPerClass)) {
        debugAssert(IAAllocationTrackerElement_getPositiveAllocationSize(element) == 0);
        debugAssert(IAAllocationTrackerElement_getNegativeAllocationSize(element) == 0);
        if (IAAllocationTrackerElement_getAllocationCount(element) != 0){
            return true;
        }
    }
    return false;
}

static void IAAllocationTracker_logMemoryLeak(IAAllocationTracker * this){
    logError("!!!Memory Leak!!!");
    char * key;
    foreach (key in autoExpandingHashMapKeys(this->allocatedObjectsPerClass)) {
        IAAllocationTrackerElement * element = IAAutoExpandingHashMap_get(this->allocatedObjectsPerClass, key);
        char prefix;
        size_t size;
        if (IAAllocationTrackerElement_getNegativeAllocationSize(element) > 0) {
            size = IAAllocationTrackerElement_getNegativeAllocationSize(element);
            prefix = '-';
            debugAssert(IAAllocationTrackerElement_getPositiveAllocationSize(element) == 0 && "Negative and positive allocation size cannot be not 0 at the same time!");
        }else{
            size = IAAllocationTrackerElement_getPositiveAllocationSize(element);
            prefix = '+';
        }
        long allocationCount = IAAllocationTrackerElement_getAllocationCount(element);
        if (allocationCount > 0) {
            logError("%s with %ld allocated objects and a total size of %c%ld.", key, allocationCount, prefix, size);
        }else if (allocationCount < 0) {
            logError("%s with %ld overreleased objects and a total size of %c%ld.", key, allocationCount, prefix, size);
        }else if (size > 0){
            logError("%s with 0 allocated objects and a total size of %c%ld.", key, prefix, size);
        }
    }
    
    foreach (key in autoExpandingHashMapKeys(this->allocatedDataPerClass)) {
        IAAllocationTrackerElement * element = IAAutoExpandingHashMap_get(this->allocatedDataPerClass, key);
        char prefix;
        size_t size;
        if (IAAllocationTrackerElement_getNegativeAllocationSize(element) > 0) {
            size = IAAllocationTrackerElement_getNegativeAllocationSize(element);
            prefix = '-';
            debugAssert(IAAllocationTrackerElement_getPositiveAllocationSize(element) == 0 && "Negative and positive allocation size cannot be not 0 at the same time!");
        }else{
            size = IAAllocationTrackerElement_getPositiveAllocationSize(element);
            prefix = '+';
        }
        long allocationCount = IAAllocationTrackerElement_getAllocationCount(element);
        if (allocationCount > 0) {
            logError("%s with %ld allocated data and a total size of %c%ld.", key, allocationCount, prefix, size);
        }else if (allocationCount < 0) {
            logError("%s with %ld overreleased data and a total size of %c%ld.", key, allocationCount, prefix, size);
        }else if (size > 0){
            logError("%s with 0 allocated data and a total size of %c%ld.", key, prefix, size);
        }
    }
    
    foreach (key in autoExpandingHashMapKeys(this->initCountPerClass)) {
        IAAllocationTrackerElement * element = IAAutoExpandingHashMap_get(this->initCountPerClass, key);
        debugAssert(IAAllocationTrackerElement_getNegativeAllocationSize(element) == 0);
        debugAssert(IAAllocationTrackerElement_getPositiveAllocationSize(element) == 0);
        long allocationCount = IAAllocationTrackerElement_getAllocationCount(element);
        if (allocationCount != 0) {
            logError("%s with an init count of %ld.", key, allocationCount);
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

void IAAllocationTracker_deinit(IAAllocationTracker * this){
    IAAutoExpandingHashMap_release(this->allocatedObjectsPerClass);
    IAAutoExpandingHashMap_release(this->allocatedDataPerClass);
    IAAutoExpandingHashMap_release(this->initCountPerClass);
    IA_decrementInitCount();
}

#endif

