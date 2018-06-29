//
//  IAAllocationTracking+Internal.h
//  CLib
//
//  Created by Konstantin Merker on 27.05.18.
//  Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAllocationTracking_Internal_h
#define IAAllocationTracking_Internal_h

#ifdef DEBUG

void IAAllocationTracking_objectAllocated(const void * object, size_t size, const char * className);
void IAAllocationTracking_objectReallocated(const void * object, size_t newSize);
void IAAllocationTracking_objectDeallocated(const void * object);

#endif

#endif
