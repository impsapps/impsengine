//
//  IALibrary.h
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 24.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineCLibrary_IALibrary_h
#define ImpsEngineCLibrary_IALibrary_h

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

/// this macro marks a constructor function
#define IA_CONSTRUCTOR

/// this macro marks a destructor function
#define IA_DESTRUCTOR

#include "IAAssert.h"
#include "IAOperatingSystem.h"

void IALibrary_commenceIfNeeded(void);

#ifdef DEBUG

#define IA_malloc(size) IALibrary_malloc(size, CLASSNAME)
#define IA_mallocWithClassName(size, className) IALibrary_malloc(size, className)
#define IA_calloc(count, size) IALibrary_calloc(count, size, CLASSNAME)
#define IA_callocWithClassName(count, size, className) IALibrary_calloc(count, size, className)
#define IA_realloc(object, size) IALibrary_realloc(object, size, CLASSNAME)
#define IA_reallocWithClassName(object, size, className) IALibrary_realloc(object, size, className)
#define IA_free(object) IALibrary_free(object, CLASSNAME);
#define IA_freeWithClassName(object, className) IALibrary_free(object, className);

void * IALibrary_malloc(size_t size, const char * className);
void * IALibrary_calloc(size_t count, size_t size, const char * className);
void * IALibrary_realloc(void * object, size_t size, const char * className);
void IALibrary_free(void* object, const char * className);

#else

#define IA_malloc(size) IALibrary_malloc(size)
#define IA_mallocWithClassName(size, className) IALibrary_malloc(size)
#define IA_calloc(count, size) IALibrary_calloc(count, size)
#define IA_callocWithClassName(count, className) IALibrary_calloc(count, size)
#define IA_realloc(object, size) IALibrary_realloc(object, size)
#define IA_reallocWithClassName(object, size, className) IALibrary_realloc(object, size)
#define IA_free(object) IALibrary_free(object);
#define IA_freeWithClassName(object, className) IALibrary_free(object);

void * IALibrary_malloc(size_t size);
void * IALibrary_calloc(size_t count, size_t size);
void * IALibrary_realloc(void * object, size_t size);
void IALibrary_free(void* object);

#endif

bool IALibrary_isDebugMode(void);

#include "IAAllocationTracking.h"
#include "IANotificationDelegate.h"

void IALibrary_registerOnMemoryWarningNotification(IANotificationDelegate * delegate);
void IALibrary_unregisterOnMemoryWarningNotification(IANotificationDelegate * delegate);

#ifdef DEBUG
#define debugOnly(e) e
#else
#define debugOnly(e)
#endif

#define swap(a, b) \
    do { \
        __typeof__(a) IA_t; \
        __typeof__(IA_t) * IA_a; \
        __typeof__(b) * IA_b; \
        IA_a  = &(a); \
        IA_b  = &(b); \
        IA_t  = *IA_a; \
        *IA_a = *IA_b; \
        *IA_b =  IA_t; \
    } while (0)


#define this this


#define in ,
#define with ,

#define list(type, ...) type, make, __VA_ARGS__
#define keys(type, ...) type, makeIteratorOverKeys, __VA_ARGS__
#define values(type, ...) type, makeIteratorOverValues, __VA_ARGS__

#define foreach(...) IA_FOREACH(__VA_ARGS__)
#define IA_FOREACH(item, type, makeIteratorMethod, ...) IA_FOREACH2(item, type, makeIteratorMethod, __COUNTER__, __VA_ARGS__)
#define IA_FOREACH2(item, type, makeIteratorMethod, counter, ...) IA_FOREACH3(item, type, makeIteratorMethod, counter, __VA_ARGS__)
#define IA_FOREACH3(item, type, makeIteratorMethod, counter, ...) IA_FOREACH4(item, type, makeIteratorMethod, IA_tempIterator ## counter, __VA_ARGS__)
#define IA_FOREACH4(item, type, makeIteratorMethod, iteratorName, ...) \
    ;type ## Iterator iteratorName; \
    type ## Iterator_ ## makeIteratorMethod(&iteratorName, (__VA_ARGS__)); \
    while((item = type ## Iterator_getNextObject(&iteratorName)) != NULL)

#include "IALogger.h"

#endif

