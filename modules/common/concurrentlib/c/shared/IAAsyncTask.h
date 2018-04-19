//
//  IAAsyncTask.h
//  Hit Verto
//
//  Created by Konstantin Merker on 02.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAAsyncTask_h
#define Hit_Verto_IAAsyncTask_h

#include <pthread.h>

typedef struct{
    pthread_t thread;
    void * data;
    void (*execute)(void * data);
} IAAsyncTask;


void IAAsyncTask_init(IAAsyncTask *);

void IAAsyncTask_execute(IAAsyncTask *, void * data, void (*execute)(void * data));

void * IAAsyncTask_wait(IAAsyncTask *);

void IAAsyncTask_deinit(IAAsyncTask *);

#include "IAAsyncTask+Generated.h"

#endif
