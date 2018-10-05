#ifndef IAParallelThread_h
#define IAParallelThread_h

#include "IAAsyncTask.h"
#include "IANotificationEvent.h"
#include "IACondition.h"

typedef struct IAParallelThread IAParallelThread;

struct IAParallelThread{
    IAAsyncTask asyncTask;
    
    void * correspondingObject;
    void (*onExecutionFinished)(void * correspondingObject, IAParallelThread * thread);
    
    void * data;
    void (*execute)(void * data);
    
    bool shouldTerminate;
    
    IACondition condition;
    IALock lock;
    
    //@set+get
    int tag;
};


void IAParallelThread_init(IAParallelThread *, void * correspondingObject, void (*onExecutionFinished)(void * correspondingObject, IAParallelThread * thread));

void IAParallelThread_execute(IAParallelThread *, void * data, void (*execute)(void * data));

void IAParallelThread_deinit(IAParallelThread *);

#include "IAParallelThread+Generated.h"

#endif
