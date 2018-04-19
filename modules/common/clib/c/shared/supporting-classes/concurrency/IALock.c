//
//  IALock.c
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 26.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IALock.h"
#include "IAAllocationTracker.h"

#define CLASSNAME "IALock"


void IALock_init(IALock * this){
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutex_init((pthread_mutex_t *) this, &attr);
    pthread_mutexattr_destroy(&attr);
    IA_increaseAllocationCount();
}

bool IALock_lock(IALock * this){
    if(pthread_mutex_lock((pthread_mutex_t *) this) == 0){
        return true;
    }else{
        return false;
    }
}
bool IALock_unlock(IALock * this){
    if(pthread_mutex_unlock((pthread_mutex_t *) this) == 0){
        return true;
    }else{
        return false;
    }
}

void IALock_deinit(IALock * this){
    pthread_mutex_destroy((pthread_mutex_t *) this);
    IA_decreaseAllocationCount();
}
