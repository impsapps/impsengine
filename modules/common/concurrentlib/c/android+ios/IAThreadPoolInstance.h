//
//  IAThreadPoolInstance.h
//  ConcurrentLib
//
//  Created by Konstantin on 22/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAThreadPoolInstance_h
#define IAThreadPoolInstance_h

#include <stdbool.h>
#include "IAParallelThread.h"

typedef struct{
    IAParallelThread parallelThread;
    bool isRunning;
} IAThreadPoolInstance;

#endif
