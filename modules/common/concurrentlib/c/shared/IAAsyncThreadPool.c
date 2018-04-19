//
//  IAAsyncThreadPool.c
//
//
//  Created by Konstantin Merker on 17/09/16.
//
//

#include "IALibrary.h"
#include "IAAsyncThreadPool.h"

#define CLASSNAME "IAAsyncThreadPool"


typedef struct{
    void * data;
    void (*execute)(void * data);
} IAAsyncThreadPool_Executeable;

void * IAAsyncThreadPool_executeAsyncFunction(IAAsyncThreadPool * this);

void IAAsyncThreadPool_init(IAAsyncThreadPool * this, int numberOfThreads){
    IAThreadPool_init(&this->threadPool, numberOfThreads);
    IACondition_init(&this->executionThreadCondition);
    IAArrayList_init(&this->executionList, 10);
    IALock_init(&this->lock);
    this->shouldTerminate = false;
    pthread_create(&this->executionThread, 0, (void * (*)(void *)) IAAsyncThreadPool_executeAsyncFunction, this);
}

void IAAsyncThreadPool_executeAsync(IAAsyncThreadPool * this, void * data, void (*execute)(void * data)){
    synchronized (&this->lock) {
        assert(this->shouldTerminate == false);
        IAAsyncThreadPool_Executeable * executeable = IA_malloc(sizeof(IAAsyncThreadPool_Executeable));
        executeable->data = data;
        executeable->execute = execute;
        IAArrayList_add(&this->executionList, executeable);
        IACondition_signal(&this->executionThreadCondition);
    }
}

void * IAAsyncThreadPool_executeAsyncFunction(IAAsyncThreadPool * this){
    synchronized (&this->lock) {
        while (true) {
            while (IAArrayList_isEmpty(&this->executionList) == false) {
                IAAsyncThreadPool_Executeable * executeable = IAArrayList_removeAtIndex(&this->executionList, 0);
                IALock_unlock(&this->lock);
                executeable->execute(executeable->data);
                IA_free(executeable);
                IALock_lock(&this->lock);
            }
            if (this->shouldTerminate) {
                break;
            }
            IACondition_wait(&this->executionThreadCondition, &this->lock);
        }
    }
    return NULL;
}

void IAAsyncThreadPool_deinit(IAAsyncThreadPool * this){
    synchronized (&this->lock) {
        this->shouldTerminate = true;
        IACondition_signal(&this->executionThreadCondition);
    }
    void * result;
    pthread_join(this->executionThread, &result);
    IAThreadPool_deinit(&this->threadPool);
    IACondition_deinit(&this->executionThreadCondition);
    IAArrayList_deinit(&this->executionList);
    IALock_deinit(&this->lock);
}


