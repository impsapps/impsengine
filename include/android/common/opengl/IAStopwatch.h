//
//  IAStopwatch.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 24.05.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IAStopwatch_h
#define ImpsEngineiOS_IAStopwatch_h

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
