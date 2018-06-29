//
//  IATime.c
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on 07.06.2015.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include <assert.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#include "IATime.h"

#define NANOSECONDSPERSECOND (uint64_t) 1000000000LL
#define MICROSECONDSPERSECOND (uint64_t) 1000000LL

static bool initialized = false;
static struct timespec startTime;
static uint64_t startTimeInNanoseconds;

void IATime_commenceIfNeeded(void){
    if (initialized == false) {
        initialized = true;
        clock_gettime(CLOCK_MONOTONIC, &startTime);
        startTimeInNanoseconds = startTime.tv_sec * NANOSECONDSPERSECOND + startTime.tv_nsec;
    }
}

uint64_t IATime_getTimeInMilliseconds(void){
	struct timespec currentTime;
	clock_gettime(CLOCK_MONOTONIC, &currentTime);
	uint64_t currentTimeInNanoseconds = currentTime.tv_sec * NANOSECONDSPERSECOND + currentTime.tv_nsec;
	return (currentTimeInNanoseconds - startTimeInNanoseconds) / MICROSECONDSPERSECOND;
}

uint64_t IATime_getTimeInNanoSeconds(void){
	struct timespec currentTime;
	clock_gettime(CLOCK_MONOTONIC, &currentTime);
	uint64_t currentTimeInNanoseconds = currentTime.tv_sec * NANOSECONDSPERSECOND + currentTime.tv_nsec;
	return currentTimeInNanoseconds - startTimeInNanoseconds;
}
