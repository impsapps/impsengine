//
//  IAThreadPoolWaitingQueueItem.h
//  ConcurrentLib
//
//  Created by Konstantin Merker on 25.07.18.
//Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAThreadPoolWaitingQueueItem_h
#define IAThreadPoolWaitingQueueItem_h

#include "IAObject.h"

typedef struct{
    //@extend
    IAObject base;
    //@get
    void * data;
    //@get
    void (*execute)(void * data);
} IAThreadPoolWaitingQueueItem;


void IAThreadPoolWaitingQueueItem_make(IAThreadPoolWaitingQueueItem * this, void * data, void (*execute)(void * data));

#include "IAThreadPoolWaitingQueueItem+Generated.h"

#endif
