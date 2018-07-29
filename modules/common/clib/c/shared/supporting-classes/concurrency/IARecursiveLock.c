//
//  IARecursiveLock.c
//  ConcurrentLib
//
//  Created by Konstantin Merker on 02/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IARecursiveLock.h"

#define CLASSNAME "IARecursiveLock"

#ifdef IA_POSIX_AVAILABLE

void IARecursiveLock_init(IARecursiveLock * this){
    this->object = IAObject_make(this);
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&this->mutex, &attr);
    pthread_mutexattr_destroy(&attr);
    IA_incrementInitCount();
}

bool IARecursiveLock_lock(IARecursiveLock * this){
    if(pthread_mutex_lock(&this->mutex) == 0){
        return true;
    }else{
        return false;
    }
}
bool IARecursiveLock_unlock(IARecursiveLock * this){
    if(pthread_mutex_unlock(&this->mutex) == 0){
        return true;
    }else{
        return false;
    }
}

void IARecursiveLock_deinit(IARecursiveLock * this){
    pthread_mutex_destroy(&this->mutex);
    IA_decrementInitCount();
}

#endif

