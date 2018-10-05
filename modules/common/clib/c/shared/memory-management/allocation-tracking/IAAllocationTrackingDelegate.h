#ifndef IAAllocationTrackingDelegate_h
#define IAAllocationTrackingDelegate_h

#ifdef DEBUG

#include <stdint.h>

//@event
typedef struct{
    void * correspondingObject;
    
    //@exe
    void (*onObjectAllocated)(void * correspondingObject, const void * objectPointer, size_t allocationSize, const char * className);
    //@exe
    void (*onObjectDeallocated)(void * correspondingObject, const void * objectPointer, size_t allocationSize, const char * className);
    
    //@exe
    void (*onDataAllocated)(void * correspondingObject, const void * dataPointer, size_t size, const char * className);
    //@exe
    void (*onDataReallocated)(void * correspondingObject, const void * oldDataPointer, const void * newDataPointer, size_t newSize, size_t oldSize, const char * className);
    //@exe
    void (*onDataDeallocated)(void * correspondingObject, const void * dataPointer, size_t size, const char * className);
    
    //@exe
    void (*onInitCountIncremented)(void * correspondingObject, const char * className);
    //@exe
    void (*onInitCountDecremented)(void * correspondingObject, const char * className);
} IAAllocationTrackingDelegate;

#include "IAAllocationTrackingDelegate+Generated.h"

#endif
#endif
