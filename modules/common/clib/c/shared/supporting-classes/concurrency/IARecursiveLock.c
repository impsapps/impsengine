//
//  IARecursiveLock.c
//  ConcurrentLib
//
//  Created by Konstantin Merker on 02/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IARecursiveLock.h"
#include <pthread.h>

#define CLASSNAME "IARecursiveLock"


void IARecursiveLock_init(IARecursiveLock * this){
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init((pthread_mutex_t *) this, &attr);
    pthread_mutexattr_destroy(&attr);
#ifdef DEBUG
    IAAllocationTracker_objectAllocated(CLASSNAME);
#endif
}

bool IARecursiveLock_lock(IARecursiveLock * this){
    if(pthread_mutex_lock((pthread_mutex_t *) this) == 0){
        return true;
    }else{
        return false;
    }
}
bool IARecursiveLock_unlock(IARecursiveLock * this){
    if(pthread_mutex_unlock((pthread_mutex_t *) this) == 0){
        return true;
    }else{
        return false;
    }
}

void IARecursiveLock_deinit(IARecursiveLock * this){
    pthread_mutex_destroy((pthread_mutex_t *) this);
#ifdef DEBUG
    IAAllocationTracker_objectDeallocated(CLASSNAME);
#endif
}

