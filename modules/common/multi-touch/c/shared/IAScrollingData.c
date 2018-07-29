//
//  IAScrollingData.c
//  MultiTouch
//
//  Created by Konstantin Merker on 26.03.18.
//  Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAScrollView.h"
#include "IATouchDelegateAttributes.h"
#include "IAArrayList.h"
#include "IAAcceleration.h"

#define CLASSNAME "IAScrollingData"

static const int IAScrollingData_numberOfLatestTouches = 10;
static const uint64_t IAScrollingData_timeDiffWhenAnEventCountsAsOld = 200;

typedef struct {
	float scrollPos;
	uint64_t time;
} IAScrollingData_TouchEvent;


void IAScrollingData_init(IAScrollingData * this, float decelerationForScrollingInPixelPerTimeUnitSquared) {
    this->base = IAObject_make(this);
	this->touch = NULL;
	this->latestTouches = IAArrayList_new(10);
	IAScrollingData_TouchEvent * latestTouchesData = IA_malloc(IAScrollingData_numberOfLatestTouches * sizeof(IAScrollingData_TouchEvent));
	this->latestTouchesData = latestTouchesData;
	for (size_t i = 0; i < IAScrollingData_numberOfLatestTouches; i++) {
		IAArrayList_add(this->latestTouches, latestTouchesData);
		latestTouchesData++;
	};
	this->numLatestTouchesSet = 0;
	this->decelerationForScrollingInPixelPerTimeUnitSquared = decelerationForScrollingInPixelPerTimeUnitSquared;
}

void IAScrollingData_startScrolling(IAScrollingData * this, const IATouch * touch) {
	this->touch = touch;
	this->numLatestTouchesSet = 0;
}

void IAScrollingData_appendNewTouchEvent(IAScrollingData * this, float scrollPos, uint64_t time) {
	IAScrollingData_TouchEvent * touchEvent;
	if (this->numLatestTouchesSet == IAScrollingData_numberOfLatestTouches) {
		touchEvent = IAArrayList_removeFirst(this->latestTouches);
		IAArrayList_add(this->latestTouches, touchEvent);
	} else {
		touchEvent = IAArrayList_get(this->latestTouches, this->numLatestTouchesSet);
		this->numLatestTouchesSet++;
	}
	*touchEvent = (IAScrollingData_TouchEvent) {
		.scrollPos = scrollPos,
		.time = time
	};
}

static void IAScrollingData_removeAllTouchEventsOlderThen(IAScrollingData * this, uint64_t time) {
	for (int i = this->numLatestTouchesSet - 1; i >= 0; i--) {
		IAScrollingData_TouchEvent * touchEvent = IAArrayList_get(this->latestTouches, i);
		if (touchEvent->time < time) {
			IAArrayList_removeAtIndex(this->latestTouches, i);
			this->numLatestTouchesSet--;
			IAArrayList_add(this->latestTouches, touchEvent);
		}
	}
}

void IAScrollingData_removeAllOldTouchEvents(IAScrollingData * this, uint64_t time) {
	if (time > IAScrollingData_timeDiffWhenAnEventCountsAsOld) {
		time -= IAScrollingData_timeDiffWhenAnEventCountsAsOld;
		IAScrollingData_removeAllTouchEventsOlderThen(this, time);
	}
}

void IAScrollingData_endScrolling(IAScrollingData * this) {
	this->touch = NULL;
}

static float IAScrollingData_getWayOfScrolling(float way, float animationBeginTime, float animationEndTime, float currentTime) {
	debugAssert(currentTime >= animationBeginTime);
	debugAssert(animationEndTime >= animationBeginTime);
	if (animationEndTime - animationBeginTime == 0) {
		return way;
	}
	if (currentTime > animationEndTime) {
		currentTime = animationEndTime;
	}
	float progress = (currentTime - animationBeginTime) / (animationEndTime - animationBeginTime);
	float result = IAAcceleration_uniformlyDecelerationFunction(0, way, progress);
	return result;
}

float IAScrollingData_getScrollPosDiffInTimeInterval(IAScrollingData * this, uint64_t timeStart, uint64_t timeEnd) {
	if (this->numLatestTouchesSet != IAScrollingData_numberOfLatestTouches) {
		return 0.0f;
	}
	IAScrollingData_TouchEvent * firstTouch = IAArrayList_getFirst(this->latestTouches);
	IAScrollingData_TouchEvent * lastTouch = IAArrayList_getLast(this->latestTouches);

	//speed in pixel per time unit
	float currentSpeed = (lastTouch->scrollPos - firstTouch->scrollPos) / (lastTouch->time - firstTouch->time);
	
	float deceleration = this->decelerationForScrollingInPixelPerTimeUnitSquared;
	if (currentSpeed < 0) {
		deceleration = -deceleration;
	}
	float duration = IAAcceleration_getDuration(currentSpeed, deceleration);
	float way = IAAcceleration_getWay(currentSpeed, deceleration);
	float animationBeginTime = lastTouch->time;
	float animationEndTime = lastTouch->time + duration;
	float wayIntervalBegin = IAScrollingData_getWayOfScrolling(way, animationBeginTime, animationEndTime, timeStart);
	float wayIntervalEnd = IAScrollingData_getWayOfScrolling(way, animationBeginTime, animationEndTime, timeEnd);
	float wayDifference = wayIntervalEnd - wayIntervalBegin;
	return wayDifference;
}

bool IAScrollingData_isScrolling(const IAScrollingData * this) {
	return this->touch != NULL;
}

bool IAScrollingData_isCurrentTouch(const IAScrollingData * this, const IATouch * touch) {
	return this->touch == touch;
}

void IAScrollingData_deinit(IAScrollingData * this) {
	IAArrayList_release(this->latestTouches);
	IA_free(this->latestTouchesData);
}

