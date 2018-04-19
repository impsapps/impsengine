//
//  IAOverscrollingBehavior.h
//  MultiTouch
//
//  Created by Konstantin Merker on 26.03.18.
//  Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAOverscrollingBehavior_h
#define IAOverscrollingBehavior_h

#include <stdint.h>

typedef struct {
	float maximumOverscrollingInPixel;
	float dragLengthToReachMaximumOverscrolling;
	float decelerationInPixelPerTimeUnitSquared;
} IAOverscrollingBehavior;

#endif
