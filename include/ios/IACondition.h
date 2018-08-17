//
//  IACondition.h
//  ConcurrentLib
//
//  Created by Konstantin on 22/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IACondition_h
#define IACondition_h

#include "IAPosixAvailable.h"

#ifdef IA_POSIX_AVAILABLE

#include "IALock.h"

//This class is basically a pthread_cond_t with an imps-engine-style interface.

typedef struct{
    //@extend
    IAObject base;
    //@getAsRef
    pthread_cond_t condition;
} IACondition;


void IACondition_init(IACondition *);

void IACondition_wait(IACondition *, IALock * lock);

void IACondition_signal(IACondition *);
void IACondition_broadcast(IACondition *);

void IACondition_deinit(IACondition *);

#include "IACondition+Generated.h"

#endif

#endif
