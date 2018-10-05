#ifndef IAStopwatch_h
#define IAStopwatch_h

#include <stdint.h>

typedef struct{
    //@get
    uint64_t startTime;
    //@get
    uint64_t currentRoundStartTime;
    unsigned int roundCount;
} IAStopwatch;


void IAStopwatch_make(IAStopwatch *);

void IAStopwatch_logRound(IAStopwatch *, const char * message);

#include "IAStopwatch+Generated.h"

#endif
