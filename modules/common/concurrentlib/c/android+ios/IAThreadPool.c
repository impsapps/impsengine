#include "IALibrary.h"
#include "IAThreadPool.h"
#include "IAThreadPoolWaitingQueueItem.h"

#define CLASSNAME "IAThreadPool"

void IAThreadPool_onExecutionFinishedCallback(IAThreadPool * this, IAParallelThread * thread);

void IAThreadPool_waitForTasksToFinishNotSynchronized(IAThreadPool * this);
bool IAThreadPool_isAnyThreadRunning(IAThreadPool * this);

void IAThreadPool_init(IAThreadPool * this, int numberOfThreads){
    this->base = IAObject_make(this);
    this->instances = IA_malloc(sizeof(IAThreadPoolInstance) * numberOfThreads);
    for (int i = 0; i < numberOfThreads; i++) {
        IAParallelThread_init(&this->instances[i].parallelThread, this, (void (*)(void *, IAParallelThread *)) IAThreadPool_onExecutionFinishedCallback);
        IAParallelThread_setTag(&this->instances[i].parallelThread, i);
        this->instances[i].isRunning = false;
    }
    this->numberOfThreads = numberOfThreads;
    IAArrayList_init(&this->waitingQueue, 10);
    IACondition_init(&this->taskFinishedCondition);
    IALock_init(&this->lock);
    this->shouldTerminate = false;
    IA_incrementInitCount();
}

void IAThreadPool_execute(IAThreadPool * this, void * data, void (*execute)(void * data)){
    synchronized (&this->lock) {
        assert(this->shouldTerminate == false);
        bool shouldAddToWaitingQueue = true;
        for (int i = 0; i < this->numberOfThreads; i++) {
            if (this->instances[i].isRunning == false) {
                IAParallelThread_execute(&this->instances[i].parallelThread, data, execute);
                shouldAddToWaitingQueue = false;
                this->instances[i].isRunning = true;
                break;
            }
        }
        if (shouldAddToWaitingQueue) {
            IAThreadPoolWaitingQueueItem * item = IAThreadPoolWaitingQueueItem_with(data, execute);
            IAArrayList_add(&this->waitingQueue, item);
        }
    }
}

void IAThreadPool_onExecutionFinishedCallback(IAThreadPool * this, IAParallelThread * thread){
    synchronized (&this->lock) {
        if (IAArrayList_isEmpty(&this->waitingQueue) == false) {
            IAThreadPoolWaitingQueueItem * item = IAArrayList_removeAtIndex(&this->waitingQueue, 0);
            void * data = IAThreadPoolWaitingQueueItem_getData(item);
            void (*execute)(void * data) = IAThreadPoolWaitingQueueItem_getExecuteFunction(item);
            IAParallelThread_execute(thread, data, execute);
        }else{
            int tag = IAParallelThread_getTag(thread);
            this->instances[tag].isRunning = false;
            IACondition_broadcast(&this->taskFinishedCondition);
        }
    }
}

void IAThreadPool_waitForTasksToFinish(IAThreadPool * this){
    synchronized (&this->lock){
        IAThreadPool_waitForTasksToFinishNotSynchronized(this);
    }
}

void IAThreadPool_waitForTasksToFinishNotSynchronized(IAThreadPool * this){
    while (IAThreadPool_isAnyThreadRunning(this)) {
        IACondition_wait(&this->taskFinishedCondition, &this->lock);
    }
    assert(IAArrayList_isEmpty(&this->waitingQueue));
}

bool IAThreadPool_isAnyThreadRunning(IAThreadPool * this){
    for (int i = 0; i < this->numberOfThreads; i++) {
        if (this->instances[i].isRunning) {
            return true;
        }
    }
    return false;
}

void IAThreadPool_deinit(IAThreadPool * this){
    synchronized (&this->lock) {
        this->shouldTerminate = true;
        IAThreadPool_waitForTasksToFinishNotSynchronized(this);
    }
    for (int i = 0; i < this->numberOfThreads; i++) {
        IAParallelThread_deinit(&this->instances[i].parallelThread);
    }
    IA_free(this->instances);
    IAArrayList_deinit(&this->waitingQueue);
    IACondition_deinit(&this->taskFinishedCondition);
    IALock_deinit(&this->lock);
    IA_decrementInitCount();
}


