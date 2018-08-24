//
//  IAAutoreleasePool.h
//  CLib
//
//  Created by Konstantin Merker on 15.07.18.
//  Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAutoreleasePool_h
#define IAAutoreleasePool_h

#include "IAPosixAvailable.h"

void IAAutoreleasePool_add(void * object);
void IAAutoreleasePool_run(void);

#if !defined(IA_POSIX_AVAILABLE)

// Manually handle autorelease context for each thread if posix threads are unavailable.
void IAAutoreleasePool_begin(void);
void IAAutoreleasePool_end(void);

#endif

#endif
