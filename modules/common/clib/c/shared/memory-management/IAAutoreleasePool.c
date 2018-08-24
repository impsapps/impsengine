//
//  IAAutoreleasePool.c
//  CLib
//
//  Created by Konstantin Merker on 15.07.18.
//  Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAAutoreleasePool.h"
#include "IAMemoryPool.h"
#include "IAAutoExpandingHashMap.h"
#include "IAPosixAvailable.h"

#undef in


#ifdef IA_POSIX_AVAILABLE

#include <pthread.h>

static pthread_once_t commence_once = PTHREAD_ONCE_INIT;

static pthread_key_t memoryPoolKey;
static pthread_key_t shouldReleaseImmediatlyCountKey;

#ifdef DEBUG
static void throwShouldRelaseImmediatlyCountNotZeroAssert(void * count){
    assert(0 && "Variable \"shouldRelaseImmediatlyCount\" should be zero at pthread exit.");
}
#endif

static void commence(void){
    pthread_key_create(&memoryPoolKey, (void (*)(void *)) IAMemoryPool_release);
#ifdef DEBUG
    pthread_key_create(&shouldReleaseImmediatlyCountKey, throwShouldRelaseImmediatlyCountNotZeroAssert);
#else
    pthread_key_create(&shouldReleaseImmediatlyCountKey, NULL);
#endif
}

static IAMemoryPool * getThreadSpecificMemoryPool(void){
    IAMemoryPool * pool;
    if ((pool = pthread_getspecific(memoryPoolKey)) == NULL) {
        pool = IAMemoryPool_new();
        pthread_setspecific(memoryPoolKey, pool);
    }
    return pool;
}

void IAAutoreleasePool_incrementShouldReleaseImmediatlyCount(void){
    pthread_once(&commence_once, commence);
    unsigned long shouldReleaseImmediatlyCount = (unsigned long) pthread_getspecific(shouldReleaseImmediatlyCountKey);
    shouldReleaseImmediatlyCount++;
    pthread_setspecific(shouldReleaseImmediatlyCountKey, (const void *) shouldReleaseImmediatlyCount);
}

void IAAutoreleasePool_decrementShouldReleaseImmediatlyCount(void){
    pthread_once(&commence_once, commence);
    unsigned long shouldReleaseImmediatlyCount = (unsigned long) pthread_getspecific(shouldReleaseImmediatlyCountKey);
    debugAssert(shouldReleaseImmediatlyCount > 0);
    shouldReleaseImmediatlyCount--;
    pthread_setspecific(shouldReleaseImmediatlyCountKey, (const void *) shouldReleaseImmediatlyCount);
}

void IAAutoreleasePool_add(void * object){
	pthread_once(&commence_once, commence);
    unsigned long shouldReleaseImmediatlyCount = (unsigned long) pthread_getspecific(shouldReleaseImmediatlyCountKey);
    if (shouldReleaseImmediatlyCount > 0) {
        IA_release(object);
    }else{
        IAMemoryPool * pool = getThreadSpecificMemoryPool();
        IAMemoryPool_add(pool, object);
    }
}

void IAAutoreleasePool_run(void){
	pthread_once(&commence_once, commence);
    IAAutoreleasePool_incrementShouldReleaseImmediatlyCount();
    IAMemoryPool * pool = getThreadSpecificMemoryPool();
    IAMemoryPool_run(pool);
    IAAutoreleasePool_decrementShouldReleaseImmediatlyCount();
}

#else

#include <windows.h>

static INIT_ONCE init_once = INIT_ONCE_STATIC_INIT;

static DWORD memoryPoolKey;
static DWORD shouldReleaseImmediatlyCountKey;

#ifdef DEBUG
static void throwShouldRelaseImmediatlyCountNotZeroAssert(void * count) {
	assert(0 && "Variable \"shouldRelaseImmediatlyCount\" should be zero at pthread exit.");
}
#endif

static BOOL InitOnceCallbackInitOnceCallback(
	PINIT_ONCE InitOnce,
	PVOID      Parameter,
	PVOID      *Context
) {
	memoryPoolKey = TlsAlloc();
	assert(memoryPoolKey != TLS_OUT_OF_INDEXES);
	shouldReleaseImmediatlyCountKey = TlsAlloc();
	assert(shouldReleaseImmediatlyCountKey != TLS_OUT_OF_INDEXES);
	return TRUE;
}

static IAMemoryPool * getThreadSpecificMemoryPool(void) {
	IAMemoryPool * pool = TlsGetValue(memoryPoolKey);
	assert(pool != NULL && "No memory pool available for current thread thread.");
	return pool;
}

void IAAutoreleasePool_incrementShouldReleaseImmediatlyCount(void) {
	InitOnceExecuteOnce(&init_once, InitOnceCallbackInitOnceCallback, NULL, NULL);
	unsigned long shouldReleaseImmediatlyCount = (unsigned long)TlsGetValue(shouldReleaseImmediatlyCountKey);
	shouldReleaseImmediatlyCount++;
	BOOL ret = TlsSetValue(shouldReleaseImmediatlyCountKey, (LPVOID)shouldReleaseImmediatlyCount);
	assert(ret);
}

void IAAutoreleasePool_decrementShouldReleaseImmediatlyCount(void) {
	InitOnceExecuteOnce(&init_once, InitOnceCallbackInitOnceCallback, NULL, NULL);
	unsigned long shouldReleaseImmediatlyCount = (unsigned long)TlsGetValue(shouldReleaseImmediatlyCountKey);
	debugAssert(shouldReleaseImmediatlyCount > 0);
	shouldReleaseImmediatlyCount--;
	BOOL ret = TlsSetValue(shouldReleaseImmediatlyCountKey, (LPVOID)shouldReleaseImmediatlyCount);
	assert(ret);
}

void IAAutoreleasePool_add(void * object) {
	InitOnceExecuteOnce(&init_once, InitOnceCallbackInitOnceCallback, NULL, NULL);
	unsigned long shouldReleaseImmediatlyCount = (unsigned long)TlsGetValue(shouldReleaseImmediatlyCountKey);
	if (shouldReleaseImmediatlyCount > 0) {
		IA_release(object);
	} else {
		IAMemoryPool * pool = getThreadSpecificMemoryPool();
		IAMemoryPool_add(pool, object);
	}
}

void IAAutoreleasePool_run(void) {
	InitOnceExecuteOnce(&init_once, InitOnceCallbackInitOnceCallback, NULL, NULL);
	IAAutoreleasePool_incrementShouldReleaseImmediatlyCount();
	IAMemoryPool * pool = getThreadSpecificMemoryPool();
	IAMemoryPool_run(pool);
	IAAutoreleasePool_decrementShouldReleaseImmediatlyCount();
}

void IAAutoreleasePool_begin(void) {
	InitOnceExecuteOnce(&init_once, InitOnceCallbackInitOnceCallback, NULL, NULL);
	IAMemoryPool * pool = IAMemoryPool_new();
	BOOL ret = TlsSetValue(memoryPoolKey, (LPVOID)pool);
	assert(ret);
	ret = TlsSetValue(shouldReleaseImmediatlyCountKey, (LPVOID)0);
	assert(ret);
}

void IAAutoreleasePool_end(void) {
	InitOnceExecuteOnce(&init_once, InitOnceCallbackInitOnceCallback, NULL, NULL);
	IAMemoryPool * pool = getThreadSpecificMemoryPool();
	IAMemoryPool_release(pool);
	assert(TlsGetValue(shouldReleaseImmediatlyCountKey) == 0 && "Variable \"shouldRelaseImmediatlyCount\" should be zero at pthread exit.");
}

#endif
