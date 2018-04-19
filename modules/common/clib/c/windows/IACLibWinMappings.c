//
//  IACLibWinMappings.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 15.03.18.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IACLibWinMappings.h"
#include "IATime.h"

static IACLibWinMappings mappings;

void IACLibWinMappings_setMappings(IACLibWinMappings mappingsTemp) {
	mappings = mappingsTemp;
}

void IATime_commence(void) {
	if (mappings.IATime_commence) {
		mappings.IATime_commence();
	}
}

uint64_t IATime_getTimeInMilliseconds(void) {
	return mappings.IATime_getTimeInMilliseconds();
}

uint64_t IATime_getTimeInNanoSeconds(void) {
	return mappings.IATime_getTimeInNanoSeconds();
}



