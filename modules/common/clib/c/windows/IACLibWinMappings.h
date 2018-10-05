#ifndef IACLibWinMappings_h
#define IACLibWinMappings_h

#include <stdint.h>

typedef struct {
	void(*IATime_commenceIfNeeded)(void);
	uint64_t(*IATime_getTimeInMilliseconds)(void);
	uint64_t(*IATime_getTimeInNanoSeconds)(void);
} IACLibWinMappings;

void IACLibWinMappings_setMappings(IACLibWinMappings mappings);

#endif
