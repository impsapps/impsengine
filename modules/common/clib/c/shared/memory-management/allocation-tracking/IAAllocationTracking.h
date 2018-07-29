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

void IAAllocationTracking_incrementInitCount(const char * className);
void IAAllocationTracking_decrementInitCount(const char * className);

#define IA_incrementInitCount() do { IAAllocationTracking_incrementInitCount(CLASSNAME); } while(0)
#define IA_incrementInitCountForClass(className) do { IAAllocationTracking_incrementInitCount(className); } while(0)
#define IA_decrementInitCount() do { IAAllocationTracking_decrementInitCount(CLASSNAME); } while(0)
#define IA_decrementInitCountForClass(className) do { IAAllocationTracking_decrementInitCount(className); } while(0)

#else

#define IA_increaseCount()
#define IA_increaseCountForClass(className)
#define IA_decreaseCount()
#define IA_decreaseCountForClass(className)

#endif

#endif
