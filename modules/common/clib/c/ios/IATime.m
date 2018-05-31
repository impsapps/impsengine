//
//  IATime.m
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 24.05.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include <assert.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <unistd.h>
#include <stdbool.h>

#include "IATime.h"

static bool initialized = false;
static uint64_t startTime;
static mach_timebase_info_data_t timebaseInfo;


void IATime_commenceIfNeeded(void){
    if (initialized == false) {
        initialized = true;
        startTime = mach_absolute_time();
        mach_timebase_info(&timebaseInfo);
    }
}

uint64_t IATime_getTimeInMilliseconds(void){
    uint64_t currentTime = mach_absolute_time();
    uint64_t timeDifference = currentTime - startTime;
    uint64_t nanoseconds = timeDifference * timebaseInfo.numer / timebaseInfo.denom;
    return (nanoseconds / 1000000);
}

uint64_t IATime_getTimeInNanoSeconds(void){
    uint64_t currentTime = mach_absolute_time();
    uint64_t timeDifference = currentTime - startTime;
    uint64_t nanoseconds = timeDifference * timebaseInfo.numer / timebaseInfo.denom;
    return nanoseconds;
}

