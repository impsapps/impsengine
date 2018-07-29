//
//  IAAutoreleasePool.h
//  CLib
//
//  Created by Konstantin Merker on 15.07.18.
//  Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAutoreleasePool_h
#define IAAutoreleasePool_h

void IAAutoreleasePool_add(void * object);
void IAAutoreleasePool_run(void);

#endif
