//
//  IAMemoryPoolElement.h
//  CLib
//
//  Created by Konstantin Merker on 15.07.18.
//Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAMemoryPoolElement_h
#define IAMemoryPoolElement_h

typedef struct{
    void * object;
} IAMemoryPoolElement;


void IAMemoryPoolElement_make(IAMemoryPoolElement * this, void * object);

void IAMemoryPoolElement_run(IAMemoryPoolElement * this);

#include "IAMemoryPoolElement+Generated.h"

#endif
