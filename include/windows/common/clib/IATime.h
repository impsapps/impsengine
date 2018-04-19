//
//  IATime.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 24.05.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IATime_h
#define ImpsEngineiOS_IATime_h

#include <stdint.h>

void IATime_commence(void);

uint64_t IATime_getTimeInMilliseconds(void);
uint64_t IATime_getTimeInNanoSeconds(void);

#endif
