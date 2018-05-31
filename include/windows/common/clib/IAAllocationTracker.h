//
//  IAAllocationTracker.h
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 25.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAllocationTracker_h
#define IAAllocationTracker_h

#include <stdbool.h>

#ifdef DEBUG

#include <pthread.h>
#include "IAAllocationTrackerDelegate.h"

void IAAllocationTracker_commence(void);

void IAAllocationTracker_register(IAAllocationTrackerDelegate * delegate);
void IAAllocationTracker_unregister(IAAllocationTrackerDelegate * delegate);

void IAAllocationTracker_terminate(void);

#define IA_increaseAllocationCount() do { IAAllocationTracker_increaseAllocationCount(CLASSNAME); } while(0)
#define IA_increaseAllocationCountForClass(className) do { IAAllocationTracker_increaseAllocationCount(className); } while(0)
#define IA_decreaseAllocationCount() do { IAAllocationTracker_decreaseAllocationCount(CLASSNAME); } while(0)
#define IA_decreaseAllocationCountForClass(className) do { IAAllocationTracker_decreaseAllocationCount(className); } while(0)

#else

#define IA_increaseAllocationCount()
#define IA_increaseAllocationCountForClass(className)
#define IA_decreaseAllocationCount()
#define IA_decreaseAllocationCountForClass(className)

#endif

#endif
