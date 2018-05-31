//
//  IAMemoryContext.h
//  CLib
//
//  Created by Konstantin Merker on 27.05.18.
//Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAMemoryContext_h
#define IAMemoryContext_h

#ifdef DEBUG

#include "IAAllocationTrackerDelegate.h"

typedef struct{
    //@extend
    IAAllocationTrackerDelegate delegate;
} IAMemoryContext;


void IAMemoryContext_init(IAMemoryContext * this);



void IAMemoryContext_deinit(IAMemoryContext * this);

#include "IAMemoryContext+Generated.h"

#endif
#endif
