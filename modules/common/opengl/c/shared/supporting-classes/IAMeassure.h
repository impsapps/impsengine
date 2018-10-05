#ifndef IAMeassure_h
#define IAMeassure_h

#include <stdint.h>

typedef struct{
    uint64_t timeInNanoSeconds;
    uint64_t pausedTimeInNanoSeconds;
} IAMeassure;

IAMeassure IAMeassure_make();

void IAMeassure_pause(IAMeassure *);
void IAMeassure_unpause(IAMeassure *);

void IAMeassure_logInfo(IAMeassure this, const char * string);
void IAMeassure_logError(IAMeassure this, const char * string);


#endif
