#include "IALibrary.h"
#include "IAThreadPoolWaitingQueueItem.h"

#define CLASSNAME "IAThreadPoolWaitingQueueItem"


void IAThreadPoolWaitingQueueItem_make(IAThreadPoolWaitingQueueItem * this, void * data, void (*execute)(void * data)){
    *this = (IAThreadPoolWaitingQueueItem){
        .base = IAObject_make(this),
        .data = data,
        .execute = execute
    };
}

