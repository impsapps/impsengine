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
    pthread_once(&commence_once, commence);
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
    unsigned long shouldReleaseImmediatlyCount = (unsigned long) pthread_getspecific(shouldReleaseImmediatlyCountKey);
    if (shouldReleaseImmediatlyCount > 0) {
        IA_release(object);
    }else{
        IAMemoryPool * pool = getThreadSpecificMemoryPool();
        IAMemoryPool_add(pool, object);
    }
}

void IAAutoreleasePool_run(void){
    IAAutoreleasePool_incrementShouldReleaseImmediatlyCount();
    IAMemoryPool * pool = getThreadSpecificMemoryPool();
    IAMemoryPool_run(pool);
    IAAutoreleasePool_decrementShouldReleaseImmediatlyCount();
}

