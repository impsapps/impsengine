//
//  IAAutoreleasePool+Internal.h
//  CLib
//
//  Created by Konstantin Merker on 24.07.18.
//  Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAutoreleasePool_Internal_h
#define IAAutoreleasePool_Internal_h

void IAAutoreleasePool_incrementShouldReleaseImmediatlyCount(void);
void IAAutoreleasePool_decrementShouldReleaseImmediatlyCount(void);

#endif
