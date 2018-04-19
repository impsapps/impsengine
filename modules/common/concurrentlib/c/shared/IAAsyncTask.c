//
//  IAAsyncTask.c
//  Hit Verto
//
//  Created by Konstantin Merker on 02.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAAsyncTask.h"
#include "IAOperatingSystem.h"
#include "IAProcess+AndroidNative.h"
#include "IAAllocationTracker.h"
#include <assert.h>

#define CLASSNAME "IAAsyncTask"


void * IAAsyncTask_executeAsyncFunction(IAAsyncTask * this);


void IAAsyncTask_init(IAAsyncTask * this){
    this->thread = NULL;
    this->data = NULL;
    this->execute = NULL;
#ifdef DEBUG
    IAAllocationTracker_objectAllocated(CLASSNAME);
#endif
}

void IAAsyncTask_execute(IAAsyncTask * this, void * data, void (*excecute)(void * data)){
    assert(this->thread == NULL && "execute: async task is already executing one task! Cannot execute multiple tasks at the same time!");
    this->data = data;
    this->execute = excecute;
    pthread_create(&(this->thread), 0, (void * (*)(void *)) IAAsyncTask_executeAsyncFunction, this);
}

void * IAAsyncTask_executeAsyncFunction(IAAsyncTask * this){
#if IA_CURRENT_OPERATING_SYSTEM == IA_OPERATING_SYSTEM_ANDROID
    IAProcess_attachToJavaVM();
#endif
    this->execute(this->data);
#if IA_CURRENT_OPERATING_SYSTEM == IA_OPERATING_SYSTEM_ANDROID
    IAProcess_detachFromJavaVM();
#endif
    return NULL;
}

void * IAAsyncTask_wait(IAAsyncTask * this){
    void * result;
    pthread_join(this->thread, &result);
    this->thread = NULL;
    this->data = NULL;
    this->execute = NULL;
    return result;
}

void IAAsyncTask_deinit(IAAsyncTask * this){
    assert(this->thread == NULL && "deinit: async task is still running! Cannot deinit resources!");
#ifdef DEBUG
    IAAllocationTracker_objectDeallocated(CLASSNAME);
#endif
}


