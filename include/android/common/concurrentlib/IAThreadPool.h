//
//  IAThreadPool.h
//  ConcurrentLib
//
//  Created by Konstantin Merker on 17/09/16.
//
//

#ifndef ConcurrentLib_IAThreadPool_h
#define ConcurrentLib_IAThreadPool_h

#include "IAThreadPoolInstance.h"

typedef struct{
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
