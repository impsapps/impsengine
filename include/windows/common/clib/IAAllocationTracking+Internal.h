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

void IAAllocationTracking_objectAllocated(const void * objectPointer, size_t size, const char * className);
void IAAllocationTracking_objectDeallocated(const void * objectPointer);

void IAAllocationTracking_dataAllocated(const void * dataPointer, size_t size, const char * className);
void IAAllocationTracking_dataReallocated(const void * oldDataPointer, const void * newDataPointer, size_t newSize);
void IAAllocationTracking_dataDeallocated(const void * dataPointer);

#endif

#endif
