#ifndef IATime_h
#define IATime_h

#include <stdint.h>

void IATime_commenceIfNeeded(void);

uint64_t IATime_getTimeInMilliseconds(void);
uint64_t IATime_getTimeInNanoSeconds(void);

#endif
