//
//  IAOverscrollingHandler.c
//  MultiTouch
//
//  Created by Konstantin Merker on 26.03.18.
//  Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAOverscrollingHandler.h"
#include "IATouchDelegateAttributes.h"
#include "IAArrayList.h"
#include "IAAcceleration.h"
#include "IAMath.h"

#define CLASSNAME "IAOverscrollingHandler"


void IAOverscrollingHandler_make(IAOverscrollingHandler * this, IAOverscrollingBehavior behavior) {
	*this = (IAOverscrollingHandler) {
		.behavior = behavior
	};
	float totalWayInPixel = this->behavior.maximumOverscrollingInPixel;
	float totalTimeInDragLength = this->behavior.dragLengthToReachMaximumOverscrolling;
	this->accelerationInPixelPerDragLengthSquared = 2.0f * totalWayInPixel / (totalTimeInDragLength * totalTimeInDragLength);
}

void IAOverscrollingHandler_appendDragLength(IAOverscrollingHandler * this, float dragLength) {
	this->currentDragLength += dragLength;
}

void IAOverscrollingHandler_modifyCurrentDragLengthIfNeeded(IAOverscrollingHandler * this, float * currentDragLengthInOut) {
	if (this->currentDragLength > 0.0f && *currentDragLengthInOut < 0.0f) {
		*currentDragLengthInOut += this->currentDragLength;
		if (*currentDragLengthInOut > 0.0f) {
			this->currentDragLength = *currentDragLengthInOut;
			*currentDragLengthInOut = 0.0f;
		} else {
			this->currentDragLength = 0.0f;
		}
	} else if (this->currentDragLength < 0.0f && *currentDragLengthInOut > 0.0f) {
		*currentDragLengthInOut += this->currentDragLength;
		if (*currentDragLengthInOut > 0.0f) {
			this->currentDragLength = *currentDragLengthInOut;
			*currentDragLengthInOut = 0.0f;
		} else {
			this->currentDragLength = 0.0f;
		}
	}
}

static float IAOverscrollingHandler_convertDragLengthToWayInPixel(IAOverscrollingHandler * this, float dragLength) {
	float currentWayInPixel = this->accelerationInPixelPerDragLengthSquared / 2.0f * (dragLength * dragLength);
	if (dragLength > 0.0f) {
		return currentWayInPixel;
	} else {
		return -currentWayInPixel;
	}
}

static float IAOverscrollingHandler_convertWayInPixelToDragLength(IAOverscrollingHandler * this, float wayInPixel) {
	float currentDragLength = sqrt(2.0f * fabsf(wayInPixel) / this->accelerationInPixelPerDragLengthSquared);
	if (wayInPixel > 0.0f) {
		return currentDragLength;
	} else {
		return -currentDragLength;
	}
}

float IAOverscrollingHandler_getAdditionalOffset(IAOverscrollingHandler * this) {
	if (this->currentDragLength > 0.0f) {
		float result = this->behavior.maximumOverscrollingInPixel - IAOverscrollingHandler_convertDragLengthToWayInPixel(this, this->behavior.dragLengthToReachMaximumOverscrolling - this->currentDragLength);
		return fminf(result, this->behavior.maximumOverscrollingInPixel);
	} else if (this->currentDragLength < 0.0f) {
		float result = -this->behavior.maximumOverscrollingInPixel + IAOverscrollingHandler_convertDragLengthToWayInPixel(this, this->behavior.dragLengthToReachMaximumOverscrolling + this->currentDragLength);
		return fmaxf(result, -this->behavior.maximumOverscrollingInPixel);
	} else {
		return 0.0f;
	}
}

void IAOverscrollingHandler_scrollBack(IAOverscrollingHandler * this, uint64_t timeUnits) {
	float totalTimeToSnapBack = sqrt(2.0f * this->behavior.maximumOverscrollingInPixel / this->behavior.decelerationInPixelPerTimeUnitSquared);
	float totalDragLength = this->behavior.dragLengthToReachMaximumOverscrolling;

	this->currentDragLength = fminf(this->currentDragLength, this->behavior.dragLengthToReachMaximumOverscrolling);
	this->currentDragLength = fmaxf(this->currentDragLength, -this->behavior.dragLengthToReachMaximumOverscrolling);

	float currentDragLength = this->currentDragLength;

	// convert length 2 times - first time to revert "IAOverscrollingHandler_getAdditionalOffset" conversion and second to make acceleration movement
	for (size_t i = 0; i < 2; i++) {
		currentDragLength = IAOverscrollingHandler_convertWayInPixelToDragLength(this, currentDragLength);
		totalDragLength = IAOverscrollingHandler_convertWayInPixelToDragLength(this, totalDragLength);
	}

	float currentTimeUnits = totalTimeToSnapBack / totalDragLength * fabsf(currentDragLength);

	if (currentTimeUnits < timeUnits) {
		this->currentDragLength = 0.0f;
		return;
	}
	currentTimeUnits -= timeUnits;

	currentDragLength = totalDragLength / totalTimeToSnapBack * currentTimeUnits;

	for (size_t i = 0; i < 2; i++) {
		currentDragLength = IAOverscrollingHandler_convertDragLengthToWayInPixel(this, currentDragLength);
	}

	if (this->currentDragLength > 0.0f) {
		this->currentDragLength = currentDragLength;
	} else {
		this->currentDragLength = -currentDragLength;
	}
}

