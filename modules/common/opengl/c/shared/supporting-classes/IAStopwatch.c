//
//  IAStopwatch.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 24.05.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAStopwatch.h"
#include "IATime.h"

#define CLASSNAME "IAStopwatch"


void IAStopwatch_make(IAStopwatch * this){
    this->startTime = IATime_getTimeInNanoSeconds();
    this->currentRoundStartTime = IATime_getTimeInNanoSeconds();
    this->roundCount = 0;
}

void IAStopwatch_logRound(IAStopwatch * this, const char * message){
    uint64_t currentTime = IATime_getTimeInNanoSeconds();
    logInfo("Round %d: Time elapsed: %llu Message: %s", this->roundCount, currentTime - this->currentRoundStartTime, message);
    this->currentRoundStartTime = currentTime;
    this->roundCount++;
    
}

