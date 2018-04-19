//
//  IACLibWinMappings.h
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 15.03.18.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IACLibWinMappings_h
#define IACLibWinMappings_h

#include <stdint.h>

typedef struct {
	void(*IATime_commence)(void);
	uint64_t(*IATime_getTimeInMilliseconds)(void);
	uint64_t(*IATime_getTimeInNanoSeconds)(void);
} IACLibWinMappings;

void IACLibWinMappings_setMappings(IACLibWinMappings mappings);

#endif
