#include "IALibrary.h"

#ifdef DEBUG

#include "IAAllocationTracking.h"
#include "IAAllocationTracking+Internal.h"
#include "IAAllocationTrackingEvent.h"
#include "IAAutoExpandingHashMap.h"
#include "IAAllocationTrackingElement.h"
#include "IAOperatingSystem.h"
#include "IACharArray.h"
#include "IARecursiveLock.h"
#include "IAAutoreleasePool+Internal.h"
#include <stdlib.h>
#include <stdint.h>

#define CLASSNAME "IAAllocationTracking"


static bool IAAllocationTracking_beginTrackingTransaction(void);
static void IAAllocationTracking_endTrackingTransaction(void);

static void IAAllocationTracking_insertTrackingElement(const void * pointer, IAAllocationTrackingElement * element);
static IAAllocationTrackingElement * IAAllocationTracking_getTrackingElement(const void * pointer);
static IAAllocationTrackingElement * IAAllocationTracking_removeTrackingElement(const void * pointer);


static IAAutoExpandingHashMap * trackingElements;
static IAAllocationTrackingEvent * event;

IA_POSIX_ONLY(static IARecursiveLock * lock);

static bool volatile isCommenced = false;
static bool isTrackingEnabled = false;

void IAAllocationTracking_commenceIfNeeded(void){
    if (isCommenced) {
        return;
    }
    IA_POSIX_ONLY(lock = IARecursiveLock_new());
    trackingElements = IAAutoExpandingHashMap_new();
    event = IAAllocationTrackingEvent_new();
    isCommenced = true;
    isTrackingEnabled = true;
}

void IAAllocationTracking_register(IAAllocationTrackingDelegate * delegate){
    IA_POSIX_ONLY(IARecursiveLock_lock(lock));
    debugAssert(isTrackingEnabled == true);
    IAAllocationTrackingEvent_register(event, delegate);
    IA_POSIX_ONLY(IARecursiveLock_unlock(lock));
}

void IAAllocationTracking_unregister(IAAllocationTrackingDelegate * delegate){
    IA_POSIX_ONLY(IARecursiveLock_lock(lock));
    debugAssert(isTrackingEnabled == true);
    IAAllocationTrackingEvent_unregister(event, delegate);
    IA_POSIX_ONLY(IARecursiveLock_unlock(lock));
}

static bool IAAllocationTracking_beginTrackingTransaction(){
    if (isCommenced == false) {
        return false;
    }
    IA_POSIX_ONLY(IARecursiveLock_lock(lock));
    if (isTrackingEnabled) {
        isTrackingEnabled = false;
        return true;
    }else{
        IA_POSIX_ONLY(IARecursiveLock_unlock(lock));
        return false;
    }
}

static void IAAllocationTracking_endTrackingTransaction(){
    debugAssert(isTrackingEnabled == false);
    isTrackingEnabled = true;
    IA_POSIX_ONLY(IARecursiveLock_unlock(lock));
}

void IAAllocationTracking_objectAllocated(const void * objectPointer, size_t size, const char * className){
    if (IAAllocationTracking_beginTrackingTransaction()) {
        IAAllocationTrackingElement * element = IAAllocationTrackingElement_new(size, className, true);
        IAAllocationTracking_insertTrackingElement(objectPointer, element);
        IAAllocationTrackingEvent_onObjectAllocated(event, objectPointer, size, className);
        IAAllocationTracking_endTrackingTransaction();
    }
}

void IAAllocationTracking_objectDeallocated(const void * objectPointer){
    if (IAAllocationTracking_beginTrackingTransaction()) {
        IAAllocationTrackingElement * element = IAAllocationTracking_removeTrackingElement(objectPointer);
        if (element) {
            debugAssert(IAAllocationTrackingElement_isObject(element));
            size_t size = IAAllocationTrackingElement_getSize(element);
            const char * className = IAAllocationTrackingElement_getClassName(element);
            IAAllocationTrackingEvent_onObjectDeallocated(event, objectPointer, size, className);
            IAAllocationTrackingElement_release(element);
        }
        IAAllocationTracking_endTrackingTransaction();
    }
}

void IAAllocationTracking_dataAllocated(const void * dataPointer, size_t size, const char * className){
    if (IAAllocationTracking_beginTrackingTransaction()) {
        IAAllocationTrackingElement * element = IAAllocationTrackingElement_new(size, className, false);
        IAAllocationTracking_insertTrackingElement(dataPointer, element);
        IAAllocationTrackingEvent_onDataAllocated(event, dataPointer, size, className);
        IAAllocationTracking_endTrackingTransaction();
    }
}

void IAAllocationTracking_dataReallocated(const void * oldDataPointer, const void * newDataPointer, size_t newSize){
    if (IAAllocationTracking_beginTrackingTransaction()) {
        IAAllocationTrackingElement * element = IAAllocationTracking_getTrackingElement(oldDataPointer);
        if (element) {
            debugAssert(IAAllocationTrackingElement_isObject(element) == false);
            size_t oldSize = IAAllocationTrackingElement_getSize(element);
            const char * className = IAAllocationTrackingElement_getClassName(element);
            IAAllocationTrackingElement_setSize(element, newSize);
            
            if (oldDataPointer != newDataPointer){
                IAAllocationTracking_removeTrackingElement(oldDataPointer);
                IAAllocationTracking_insertTrackingElement(newDataPointer, element);
            }
            IAAllocationTrackingEvent_onDataReallocated(event, oldDataPointer, newDataPointer, newSize, oldSize, className);
        }
        IAAllocationTracking_endTrackingTransaction();
    }
}

void IAAllocationTracking_dataDeallocated(const void * dataPointer){
    if (IAAllocationTracking_beginTrackingTransaction()) {
        IAAllocationTrackingElement * element = IAAllocationTracking_removeTrackingElement(dataPointer);
        if (element) {
            debugAssert(IAAllocationTrackingElement_isObject(element) == false);
            size_t size = IAAllocationTrackingElement_getSize(element);
            const char * className = IAAllocationTrackingElement_getClassName(element);
            IAAllocationTrackingEvent_onDataDeallocated(event, dataPointer, size, className);
            IAAllocationTrackingElement_release(element);
        }
        IAAllocationTracking_endTrackingTransaction();
    }
}

static void IAAllocationTracking_insertTrackingElement(const void * pointer, IAAllocationTrackingElement * element){
    debugAssert(isTrackingEnabled == false);
    char objectKey[IA_KEY_SIZE_FOR_OBJECT];
    IAHashMap_getKeyForObject(pointer, objectKey);
    debugAssert(IAAutoExpandingHashMap_containsKey(trackingElements, objectKey) == false);
    IAAutoExpandingHashMap_add(trackingElements, objectKey, element);
}

static IAAllocationTrackingElement * IAAllocationTracking_getTrackingElement(const void * pointer){
    debugAssert(isTrackingEnabled == false);
    char objectKey[IA_KEY_SIZE_FOR_OBJECT];
    IAHashMap_getKeyForObject(pointer, objectKey);
    IAAllocationTrackingElement * element = IAAutoExpandingHashMap_get(trackingElements, objectKey);
    return element;
}

static IAAllocationTrackingElement * IAAllocationTracking_removeTrackingElement(const void * pointer){
    debugAssert(isTrackingEnabled == false);
    char objectKey[IA_KEY_SIZE_FOR_OBJECT];
    IAHashMap_getKeyForObject(pointer, objectKey);
    IAAutoreleasePool_incrementShouldReleaseImmediatlyCount();
    IAAllocationTrackingElement * element = IAAutoExpandingHashMap_remove(trackingElements, objectKey);
    IAAutoreleasePool_decrementShouldReleaseImmediatlyCount();
    return element;
}

void IAAllocationTracking_incrementInitCount(const char * className){
    if (IAAllocationTracking_beginTrackingTransaction()) {
        IAAllocationTrackingEvent_onInitCountIncremented(event, className);
        IAAllocationTracking_endTrackingTransaction();
    }
}

void IAAllocationTracking_decrementInitCount(const char * className){
    if (IAAllocationTracking_beginTrackingTransaction()) {
        IAAllocationTrackingEvent_onInitCountDecremented(event, className);
        IAAllocationTracking_endTrackingTransaction();
    }
}

#endif
