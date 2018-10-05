#ifndef IAOverscrollingHandler_h
#define IAOverscrollingHandler_h

#include "IAOverscrollingBehavior.h"
#include "IAObject.h"

typedef struct{
    //@extend
    IAObject base;
    float currentDragLength;
	IAOverscrollingBehavior behavior;
	float accelerationInPixelPerDragLengthSquared;
} IAOverscrollingHandler;


void IAOverscrollingHandler_make(IAOverscrollingHandler *, IAOverscrollingBehavior behavior);

void IAOverscrollingHandler_appendDragLength(IAOverscrollingHandler *, float dragLength);
void IAOverscrollingHandler_modifyCurrentDragLengthIfNeeded(IAOverscrollingHandler *, float * currentDragLengthInOut);

float IAOverscrollingHandler_getAdditionalOffset(IAOverscrollingHandler * this);
void IAOverscrollingHandler_scrollBack(IAOverscrollingHandler * this, uint64_t timeUnits);

#include "IAOverscrollingHandler+Generated.h"

#endif
