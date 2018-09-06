//
//  IAThreadPoolWaitingQueueItem.c
//  ConcurrentLib
//
//  Created by Konstantin Merker on 25.07.18.
//Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

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

