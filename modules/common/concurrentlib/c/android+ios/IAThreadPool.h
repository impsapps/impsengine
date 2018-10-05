#ifndef IAThreadPool_h
#define IAThreadPool_h

#include "IAThreadPoolInstance.h"
#include "IAArrayList.h"

typedef struct{
    //@extend
    IAObject base;
    IAThreadPoolInstance * instances;
    int numberOfThreads;
    IAArrayList waitingQueue;
    IACondition taskFinishedCondition;
    IALock lock;
    bool shouldTerminate;
} IAThreadPool;


void IAThreadPool_init(IAThreadPool *, int numberOfThreads);

void IAThreadPool_execute(IAThreadPool *, void * data, void (*execute)(void * data));

void IAThreadPool_waitForTasksToFinish(IAThreadPool *);

void IAThreadPool_deinit(IAThreadPool *);

#include "IAThreadPool+Generated.h"

#endif
