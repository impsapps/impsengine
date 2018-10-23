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
    void * data = malloc(size);
    while (data == NULL) {
        IALibrary_onMemoryWarning();
	    data = malloc(size);
    }
    IAAllocationTracking_dataAllocated(data, size, className);
    return data;
}

void * IALibrary_calloc(size_t count, size_t size, const char * className){
    IALibrary_checkIfLibraryIsCommenced();
    void * data = calloc(count, size);
    while (data == NULL) {
        IALibrary_onMemoryWarning();
	    data = calloc(count, size);
    }
    IAAllocationTracking_dataAllocated(data, size, className);
    return data;
}

void * IALibrary_realloc(void * data, size_t size, const char * className){
    IALibrary_checkIfLibraryIsCommenced();
    void * newData = realloc(data, size);
    while (newData == NULL) {
        IALibrary_onMemoryWarning();
	    newData = realloc(data, size);
    }
    IAAllocationTracking_dataReallocated(data, newData, size);
    return newData;
}

void IALibrary_free(void * data, const char * className){
    IALibrary_checkIfLibraryIsCommenced();
    free(data);
    IAAllocationTracking_dataDeallocated(data);
}

#else

void * IALibrary_new(size_t size, void (*deinit)(void * object)){
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

void IALibrary_retain(void * object){
	object = *(void **)object;
    IAObjectInformation * information = object;
    information -= 1;
    information->allocationCount++;
}

void IALibrary_autorelease(void * object){
    IAAutoreleasePool_add(object);
}

void IALibrary_release(void * object){
	object = *(void **)object;
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
    void * data = malloc(size);
    while (data == NULL) {
        IALibrary_onMemoryWarning();
        data = malloc(size);
    }
    return data;
}

void * IALibrary_calloc(size_t count, size_t size){
    void * data = calloc(count, size);
    while (data == NULL) {
        IALibrary_onMemoryWarning();
        data = calloc(count, size);
    }
    return data;
}

void * IALibrary_realloc(void * data, size_t size){
    void * newData = realloc(data, size);
    while (newData == NULL) {
        IALibrary_onMemoryWarning();
        newData = realloc(data, size);
    }
    return newData;
}

void IALibrary_free(void * data){
    free(data);
}

#endif

bool IALibrary_isDebugMode(void){
#ifdef DEBUG
    return true;
#else
    return false;
#endif
}

