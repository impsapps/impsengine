#ifndef IAOverscrollingBehavior_h
#define IAOverscrollingBehavior_h

#include <stdint.h>

typedef struct {
	float maximumOverscrollingInPixel;
	float dragLengthToReachMaximumOverscrolling;
	float decelerationInPixelPerTimeUnitSquared;
} IAOverscrollingBehavior;

#endif
