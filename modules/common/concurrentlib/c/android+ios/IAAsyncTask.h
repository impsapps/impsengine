#ifndef IAAsyncTask_h
#define IAAsyncTask_h

#include <pthread.h>
#include "IAObject.h"

typedef struct{
    //@extend
    IAObject base;
    pthread_t thread;
    void * data;
    void (*execute)(void * data);
} IAAsyncTask;


void IAAsyncTask_init(IAAsyncTask *);

void IAAsyncTask_execute(IAAsyncTask *, void * data, void (*execute)(void * data));

void IAAsyncTask_wait(IAAsyncTask *);

void IAAsyncTask_deinit(IAAsyncTask *);

#include "IAAsyncTask+Generated.h"

#endif
