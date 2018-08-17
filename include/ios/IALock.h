//
//  IALock.h
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 26.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineCLibrary_IALock_h
#define ImpsEngineCLibrary_IALock_h

#include "IAPosixAvailable.h"
#include "IAObject.h"

#ifdef IA_POSIX_AVAILABLE

#include <pthread.h>
#include <stdbool.h>

/// This class is basically a pthread_mutex_t with an imps-engine-style interface.

typedef struct{
    //@extend
    IAObject base;
    //@getAsRef
    pthread_mutex_t mutex;
} IALock;


void IALock_init(IALock *);

bool IALock_lock(IALock *);
bool IALock_unlock(IALock *);

void IALock_deinit(IALock *);

#include "IALock+Generated.h"


#define synchronized(lock) IA_SYNCHRONIZED(lock, __COUNTER__)

#define IA_SYNCHRONIZED(lock, counter) IA_SYNCHRONIZED2(lock, counter)
#define IA_SYNCHRONIZED2(lock, counter) IA_SYNCHRONIZED3(lock, IA_tempLock ## counter, IA_tempBoolean ## counter)
#define IA_SYNCHRONIZED3(lock, tempLock, tempBoolean) \
    IALock * tempLock = lock; \
    IALock_lock( tempLock ); \
    for(bool tempBoolean = false; tempBoolean == false || (IALock_unlock( tempLock ) && 1==2); tempBoolean = true)

#endif

#endif

