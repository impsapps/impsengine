//
//  IAAllocationTracking.h
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 25.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAllocationTracking_h
#define IAAllocationTracking_h

#include <stdbool.h>

#ifdef DEBUG

#include <pthread.h>
#include "IAAllocationTrackingDelegate.h"

void IAAllocationTracking_commenceIfNeeded(void);

void IAAllocationTracking_register(IAAllocationTrackingDelegate * delegate);
void IAAllocationTracking_unregister(IAAllocationTrackingDelegate * delegate);

void IAAllocationTracking_increaseAllocationCount(const char * className);
void IAAllocationTracking_decreaseAllocationCount(const char * className);

#define IA_increaseAllocationCount() do { IAAllocationTracking_increaseAllocationCount(CLASSNAME); } while(0)
#define IA_increaseAllocationCountForClass(className) do { IAAllocationTracking_increaseAllocationCount(className); } while(0)
#define IA_decreaseAllocationCount() do { IAAllocationTracking_decreaseAllocationCount(CLASSNAME); } while(0)
#define IA_decreaseAllocationCountForClass(className) do { IAAllocationTracking_decreaseAllocationCount(className); } while(0)

#else

#define IA_increaseAllocationCount()
#define IA_increaseAllocationCountForClass(className)
#define IA_decreaseAllocationCount()
#define IA_decreaseAllocationCountForClass(className)

#endif

#endif
