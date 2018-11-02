#ifndef IAScrollingData_h
#define IAScrollingData_h

#include <stdint.h>
#include "IAObject.h"
#include "IATouch.h"
#include "IAStructArrayList.h"

typedef struct {
	float scrollPos;
	uint64_t time;
} IAScrollingData_TouchEvent;

IA_STRUCT_ARRAY_LIST(IAScrollingData_TouchEvent);


typedef struct{
    //@extend
    IAObject base;
	IATouch touch;
	bool isTouchSet;
	IAStructArrayList_IAScrollingData_TouchEvent * latestTouchesData;
	float decelerationForScrollingInPixelPerTimeUnitSquared;
} IAScrollingData;


void IAScrollingData_init(IAScrollingData *, float decelerationForScrollingInPixelPerTimeUnitSquared);

void IAScrollingData_startScrolling(IAScrollingData *, IATouch touch);

void IAScrollingData_appendNewTouchEvent(IAScrollingData *, float scrollPos, uint64_t time);
void IAScrollingData_removeAllOldTouchEvents(IAScrollingData *, uint64_t time);

void IAScrollingData_endScrolling(IAScrollingData *);

float IAScrollingData_getScrollPosDiffInTimeInterval(IAScrollingData *, uint64_t timeStart, uint64_t timeEnd);

bool IAScrollingData_isScrolling(const IAScrollingData *);
bool IAScrollingData_isCurrentTouch(const IAScrollingData *, IATouch touch);

void IAScrollingData_deinit(IAScrollingData *);

#include "IAScrollingData+Generated.h"

#endif
