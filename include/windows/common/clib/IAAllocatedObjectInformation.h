//
//  IAAllocatedObjectInformation.h
//  CLib
//
//  Created by Konstantin Merker on 27.05.18.
//Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAllocatedObjectInformation_h
#define IAAllocatedObjectInformation_h

#ifdef DEBUG

typedef struct{
    //@set+get
    size_t size;
    //@getAsConst
    char * className;
} IAAllocatedObjectInformation;


void IAAllocatedObjectInformation_init(IAAllocatedObjectInformation *, size_t size, const char * className);

void IAAllocatedObjectInformation_increaseSize(IAAllocatedObjectInformation *, size_t increment);
void IAAllocatedObjectInformation_decreaseSize(IAAllocatedObjectInformation *, size_t decrement);

void IAAllocatedObjectInformation_deinit(IAAllocatedObjectInformation *);

#include "IAAllocatedObjectInformation+Generated.h"

#endif

#endif
