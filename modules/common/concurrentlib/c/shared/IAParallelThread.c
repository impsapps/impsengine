//
//  IAParallelThread.c
//  ConcurrentLib
//
//  Created by Konstantin Merker on 17/09/16.
//
//

#include "IALibrary.h"
#include "IAParallelThread.h"

#define CLASSNAME "IAParallelThread"


void IAParallelThread_executeAsyncFunction(IAParallelThread * this);

void IAParallelThread_init(IAParallelThread * this, void * correspondingObject, void (*onExecutionFinished)(void * correspondingObject, IAParallelThread * thread)){
    IAAsyncTask_init(&this->asyncTask);
    this->correspondingObject = correspondingObject;
    this->onExecutionFinished = onExecutionFinished;
    this->data = NULL;
    this->execute = NULL;
    this->shouldTerminate = false;
    IACondition_init(&this->condition);
    IALock_init(&this->lock);
    this->tag = 0;
    IAAsyncTask_execute(&this->asyncTask, this, (void (*)(void *)) IAParallelThread_executeAsyncFunction);
}

void IAParallelThread_executeOnParallelThread(IAParallelThread * this, void * data, void (*execute)(void * data)){
    synchronized (&this->lock) {
        assert(this->data == NULL && "executeOnParallelThread: Already running a task on parallel thread! Cannot execute multiple threads at the same time!");
        assert(this->shouldTerminate == false && "executeOnParallelThread: parallel thread is terminated! Function \"deinit\" already called!");
        this->data = data;
        this->execute = execute;
        IACondition_signal(&this->condition);
    }
}

void IAParallelThread_executeAsyncFunction(IAParallelThread * this){
    synchronized (&this->lock) {
        while (true) {
            while (this->data != NULL) {
                this->execute(this->data);
                this->data = NULL;
                this->execute = NULL;
                IALock_unlock(&this->lock);
                if (this->onExecutionFinished != NULL) {
                    this->onExecutionFinished(this->correspondingObject, this);
                }
                IALock_lock(&this->lock);
            }
            
            if (this->shouldTerminate) {
                break;
            }
            
            IACondition_wait(&this->condition, &this->lock);
        }
    }
}

void IAParallelThread_deinit(IAParallelThread * this){
    synchronized (&this->lock){
        this->shouldTerminate = true;
        IACondition_signal(&this->condition);
    }
    
    IAAsyncTask_wait(&this->asyncTask);
    IAAsyncTask_deinit(&this->asyncTask);
    IACondition_deinit(&this->condition);
    IALock_deinit(&this->lock);
}


