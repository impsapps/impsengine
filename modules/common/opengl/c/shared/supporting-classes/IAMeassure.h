//
//  IAMeassure.h
//  ImpsEngine
//
//  Created by Konstantin Merker on 26/04/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngine_IAMeassure_h
#define ImpsEngine_IAMeassure_h

#include <stdint.h>

typedef struct{
    uint64_t timeInNanoSeconds;
    uint64_t pausedTimeInNanoSeconds;
} IAMeassure;

IAMeassure IAMeassure_make();

void IAMeassure_pause(IAMeassure *);
void IAMeassure_unpause(IAMeassure *);

void IAMeassure_logInfo(IAMeassure this, const char * string);
void IAMeassure_logError(IAMeassure this, const char * string);


#endif
