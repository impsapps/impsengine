//
//  IAAsyncThreadPool.h
//  
//
//  Created by Konstantin Merker on 17/09/16.
//
//

#ifndef _IAAsyncThreadPool_h
#define _IAAsyncThreadPool_h

#include "IAThreadPool.h"

typedef struct{
    IAThreadPool threadPool;
    pthread_t executionThread;
    IACondition executionThreadCondition;
    IAArrayList executionList;
    IALock lock;
    bool shouldTerminate;
} IAAsyncThreadPool;


void IAAsyncThreadPool_init(IAAsyncThreadPool *, int numberOfThreads);

void IAAsyncThreadPool_executeAsync(IAAsyncThreadPool *, void * data, void (*execute)(void * data));

void IAAsyncThreadPool_deinit(IAAsyncThreadPool *);

#include "IAAsyncThreadPool+Generated.h"

#endif
