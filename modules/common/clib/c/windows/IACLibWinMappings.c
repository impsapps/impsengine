#include "IACLibWinMappings.h"
#include "IATime.h"

static IACLibWinMappings mappings;

void IACLibWinMappings_setMappings(IACLibWinMappings mappingsTemp) {
	mappings = mappingsTemp;
}

void IATime_commenceIfNeeded(void) {
	if (mappings.IATime_commenceIfNeeded) {
		mappings.IATime_commenceIfNeeded();
	}
}

uint64_t IATime_getTimeInMilliseconds(void) {
	return mappings.IATime_getTimeInMilliseconds();
}

uint64_t IATime_getTimeInNanoSeconds(void) {
	return mappings.IATime_getTimeInNanoSeconds();
}



