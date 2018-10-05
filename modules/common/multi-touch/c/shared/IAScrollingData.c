#include "IALibrary.h"
#include "IAScrollView.h"
#include "IATouchDelegateAttributes.h"
#include "IAArrayList.h"
#include "IAAcceleration.h"

#define CLASSNAME "IAScrollingData"

static const int IAScrollingData_numberOfLatestTouches = 10;
static const uint64_t IAScrollingData_timeDiffWhenAnEventCountsAsOld = 200;


void IAScrollingData_init(IAScrollingData * this, float decelerationForScrollingInPixelPerTimeUnitSquared) {
    this->base = IAObject_make(this);
	this->isTouchSet = false;
	IA_STRUCT_ARRAY_LIST_MALLOC_MAKE(this->latestTouchesData, IAScrollingData_TouchEvent, IAScrollingData_numberOfLatestTouches);
	this->decelerationForScrollingInPixelPerTimeUnitSquared = decelerationForScrollingInPixelPerTimeUnitSquared;
	IA_incrementInitCount();
}

void IAScrollingData_startScrolling(IAScrollingData * this, const IATouch touch) {
	this->touch = touch;
	this->isTouchSet = true;
}

void IAScrollingData_appendNewTouchEvent(IAScrollingData * this, float scrollPos, uint64_t time) {
	if (IAStructArrayList_IAScrollingData_TouchEvent_getCurrentSize(this->latestTouchesData) == IAScrollingData_numberOfLatestTouches) {
		IAStructArrayList_IAScrollingData_TouchEvent_removeFirst(this->latestTouchesData);

	}
	IAScrollingData_TouchEvent touchEvent = (IAScrollingData_TouchEvent) {
		.scrollPos = scrollPos,
		.time = time
	};
	IAStructArrayList_IAScrollingData_TouchEvent_add(this->latestTouchesData, touchEvent);
}

static void IAScrollingData_removeAllTouchEventsOlderThen(IAScrollingData * this, uint64_t time) {
	size_t i = IAStructArrayList_IAScrollingData_TouchEvent_getCurrentSize(this->latestTouchesData);
	while (i > 0){
		i--;
		IAScrollingData_TouchEvent touchEvent = IAStructArrayList_IAScrollingData_TouchEvent_get(this->latestTouchesData, i);
		if (touchEvent.time < time) {
			IAStructArrayList_IAScrollingData_TouchEvent_removeAtIndex(this->latestTouchesData, i);
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
	this->isTouchSet = false;
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
	if (IAStructArrayList_IAScrollingData_TouchEvent_getCurrentSize(this->latestTouchesData) != IAScrollingData_numberOfLatestTouches) {
		return 0.0f;
	}
	IAScrollingData_TouchEvent firstTouch = IAStructArrayList_IAScrollingData_TouchEvent_getFirst(this->latestTouchesData);
	IAScrollingData_TouchEvent lastTouch = IAStructArrayList_IAScrollingData_TouchEvent_getLast(this->latestTouchesData);

	//speed in pixel per time unit
	float currentSpeed = (lastTouch.scrollPos - firstTouch.scrollPos) / (lastTouch.time - firstTouch.time);
	
	float deceleration = this->decelerationForScrollingInPixelPerTimeUnitSquared;
	if (currentSpeed < 0) {
		deceleration = -deceleration;
	}
	float duration = IAAcceleration_getDuration(currentSpeed, deceleration);
	float way = IAAcceleration_getWay(currentSpeed, deceleration);
	float animationBeginTime = lastTouch.time;
	float animationEndTime = lastTouch.time + duration;
	float wayIntervalBegin = IAScrollingData_getWayOfScrolling(way, animationBeginTime, animationEndTime, timeStart);
	float wayIntervalEnd = IAScrollingData_getWayOfScrolling(way, animationBeginTime, animationEndTime, timeEnd);
	float wayDifference = wayIntervalEnd - wayIntervalBegin;
	return wayDifference;
}

bool IAScrollingData_isScrolling(const IAScrollingData * this) {
	if (this->isTouchSet == false){
		return false;
	}else{
		return true;
	}
}

bool IAScrollingData_isCurrentTouch(const IAScrollingData * this, IATouch touch) {
	if (this->isTouchSet == false){
		return false;
	}
	return IATouch_hasSameIdentifier(this->touch, touch);
}

void IAScrollingData_deinit(IAScrollingData * this) {
	IA_STRUCT_ARRAY_LIST_FREE(this->latestTouchesData);
	IA_decrementInitCount();
}

