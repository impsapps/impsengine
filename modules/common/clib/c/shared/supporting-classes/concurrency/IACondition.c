//
//  IACondition.c
//  ConcurrentLib
//
//  Created by Konstantin on 22/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IACondition.h"
#include "IAAllocationTracker.h"

#define CLASSNAME "IACondition"


void IACondition_init(IACondition * this){
    pthread_condattr_t condattr;
    pthread_condattr_init(&condattr);
    pthread_cond_init(&this->condition, &condattr);
    pthread_condattr_destroy(&condattr);
#ifdef DEBUG
    IAAllocationTracker_objectAllocated(CLASSNAME);
#endif
}

void IACondition_wait(IACondition * this, IALock * lock){
    pthread_mutex_t * mutex = IALock_getMutex(lock);
    pthread_cond_wait(&this->condition, mutex);
}

void IACondition_signal(IACondition * this){
    pthread_cond_signal(&this->condition);
}

void IACondition_broadcast(IACondition * this){
    pthread_cond_broadcast(&this->condition);
}

void IACondition_deinit(IACondition * this){
    pthread_cond_destroy(&this->condition);
#ifdef DEBUG
    IAAllocationTracker_objectDeallocated(CLASSNAME);
#endif
}

