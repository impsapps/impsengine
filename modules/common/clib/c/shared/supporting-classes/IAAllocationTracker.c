//
//  IAAllocationTracker.c
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 25.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAAllocationTracker.h"
#include "IAAutoExpandingHashMap.h"
#include "IAOperatingSystem.h"
#include "IACharArray.h"

#define CLASSNAME "IAAllocationTracker"

#ifdef DEBUG

#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

static const int numberOfContexts = 8;

static IAAutoExpandingHashMap * allocationCounts[numberOfContexts];
static int currentTrackingContext = IA_TRACKING_CONTEXT_DEFAULT;
static pthread_mutex_t mutex;
static bool shouldAnalyse = false;

void IAAllocationTracker_commence(void){
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex, &attr);
    for (int i = 0; i < numberOfContexts; i++) {
        allocationCounts[i] = IAAutoExpandingHashMap_new();
    }
    shouldAnalyse = true;
}

int IAAllocationTracker_getContext(void){
    return currentTrackingContext;
}

void IAAllocationTracker_setContext(int trackingContext){
    currentTrackingContext = trackingContext;
}

static IAAutoExpandingHashMap * IAAllocationTracker_getCurrentAllocationCounts(void){
    int index = currentTrackingContext - IA_TRACKING_CONTEXT_0;
    return allocationCounts[index];
}

void IAAllocationTracker_objectAllocated(const char * className){
    pthread_mutex_lock(&mutex);
    if (shouldAnalyse == true) {
        shouldAnalyse = false;
        IAAutoExpandingHashMap * currentAllocationCounts = IAAllocationTracker_getCurrentAllocationCounts();
        int * value = IAAutoExpandingHashMap_get(currentAllocationCounts, className);
        if (value == NULL) {
            value = malloc(sizeof(int));
            *value = 0;
            IAAutoExpandingHashMap_add(currentAllocationCounts, className, value);
        }
        (*value)++;
        shouldAnalyse = true;
    }
    pthread_mutex_unlock(&mutex);
}

void IAAllocationTracker_objectDeallocated(const char * className){
    pthread_mutex_lock(&mutex);
    if (shouldAnalyse == true) {
        shouldAnalyse = false;
        IAAutoExpandingHashMap * currentAllocationCounts = IAAllocationTracker_getCurrentAllocationCounts();
        int * value = IAAutoExpandingHashMap_get(currentAllocationCounts, className);
        assert (value != NULL && "object in a class got released which wasn't allocated");
        (*value)--;
        assert (*value >= 0 && "object in a class got overReleased");
        shouldAnalyse = true;
    }
    pthread_mutex_unlock(&mutex);
}

int IAAllocationTracker_getCurrentAllocationCountForObject(const char * className){
    pthread_mutex_lock(&mutex);
    IAAutoExpandingHashMap * currentAllocationCounts = IAAllocationTracker_getCurrentAllocationCounts();
    int * value = IAAutoExpandingHashMap_get(currentAllocationCounts, className);
    int result = 0;
    if (value) {
        result = *value;
    }
    pthread_mutex_unlock(&mutex);
    return result;
}

bool IAAllocationTracker_areObjectsAllocated(void){
    pthread_mutex_lock(&mutex);
    IAAutoExpandingHashMap * currentAllocationCounts = IAAllocationTracker_getCurrentAllocationCounts();
    IAAutoExpandingHashMapIterator iterator;
    IAAutoExpandingHashMapIterator_makeIteratorOverValues(&iterator, currentAllocationCounts);
    int * value;
    bool areObjectsAllocated = false;
    while ((value = IAAutoExpandingHashMapIterator_getNextObject(&iterator)) != NULL) {
        if (*value != 0) {
            areObjectsAllocated = true;
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
    return areObjectsAllocated;
}

static void IAAllocationTracker_logMemoryLeak(void){
    logError("!!!Memory Leak!!!");
    IAAutoExpandingHashMap * currentAllocationCounts = IAAllocationTracker_getCurrentAllocationCounts();
    char * key;
    foreach (key in autoExpandingHashMapKeys(currentAllocationCounts)) {
        int * value = IAAutoExpandingHashMap_get(currentAllocationCounts, key);
        if (*value > 0) {
            logError("%s with %d allocated objects.", key, *value);
        }
        if (*value < 0) {
            logError("%s with %d overreleased objects.", key, *value);
        }
    }
}

void IAAllocationTracker_log(void){
    pthread_mutex_lock(&mutex);
    if (IAAllocationTracker_areObjectsAllocated()) {
        IAAllocationTracker_logMemoryLeak();
    }else{
        logInfo("Everything ok!");
    }
    pthread_mutex_unlock(&mutex);
}

void IAAllocationTracker_assert(void){
    pthread_mutex_lock(&mutex);
    assert(IAAllocationTracker_areObjectsAllocated() == false && "Memory leaks detected!");
    pthread_mutex_unlock(&mutex);
}

void IAAllocationTracker_terminate(void){
    shouldAnalyse = false;
    for (int i = 0; i < numberOfContexts; i++) {
        IAAutoExpandingHashMap_release(allocationCounts[i]);
    }
    pthread_mutex_destroy(&mutex);
}


#endif
