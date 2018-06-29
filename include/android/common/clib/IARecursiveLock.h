//
//  IARecursiveLock.h
//  ConcurrentLib
//
//  Created by Konstantin Merker on 02/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IARecursiveLock_h
#define IARecursiveLock_h

#include "IAPosixAvailable.h"

#ifdef IA_POSIX_AVAILABLE

#include <pthread.h>

/// This class is basically a recursive pthread_mutex_t with an imps-engine-style interface.

typedef struct{
    //@getAsRef
    pthread_mutex_t mutex;
} IARecursiveLock;


void IARecursiveLock_init(IARecursiveLock *);

bool IARecursiveLock_lock(IARecursiveLock *);
bool IARecursiveLock_unlock(IARecursiveLock *);

void IARecursiveLock_deinit(IARecursiveLock *);

#include "IARecursiveLock+Generated.h"


#define synchronized_r(recursiveLock) IA_SYNCHRONIZED_R(recursiveLock, __COUNTER__)

#define IA_SYNCHRONIZED_R(recursiveLock, counter) IA_SYNCHRONIZED_R2(recursiveLock, counter)
#define IA_SYNCHRONIZED_R2(recursiveLock, counter) IA_SYNCHRONIZED_R3(recursiveLock, IA_tempLock ## counter, IA_tempBoolean ## counter)
#define IA_SYNCHRONIZED_R3(recursiveLock, tempLock, tempBoolean) \
    IARecursiveLock * tempLock = recursiveLock; \
    IARecursiveLock_lock( tempLock ); \
    for(bool tempBoolean = false; tempBoolean == false || (IARecursiveLock_unlock( tempLock ) && 1==2); tempBoolean = true)

#endif

#endif
