//
//  IAAppEntryPoint+Core.h
//  Core
//
//  Created by Konstantin Merker on 12/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAppEntryPoint_Core_h
#define IAAppEntryPoint_Core_h

#include "IAAppEntryPoint.h"

IAInterfaceOrientationMask IAAppEntryPoint_getInterfaceOrientationMask();
void IAAppEntryPoint_onAppStart(IAAppAttributes * attributesOut);

#endif
