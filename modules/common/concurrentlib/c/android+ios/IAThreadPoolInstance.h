#ifndef IAThreadPoolInstance_h
#define IAThreadPoolInstance_h

#include <stdbool.h>
#include "IAParallelThread.h"

typedef struct{
    IAParallelThread parallelThread;
    bool isRunning;
} IAThreadPoolInstance;

#endif
