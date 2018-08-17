//
//  IAAppEntryPoint.h
//  Core
//
//  Created by Konstantin Merker on 12/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAppEntryPoint_h
#define IAAppEntryPoint_h

#include "IAInterfaceOrientationMask.h"
#include "IAAppAttributes.h"

void IAAppEntryPoint_setInterfaceOrientationMask(IAInterfaceOrientationMask interfaceOrientationMask);
void IAAppEntryPoint_setOnAppStart(void (*onAppStart)(IAAppAttributes * attributesOut));

#endif
