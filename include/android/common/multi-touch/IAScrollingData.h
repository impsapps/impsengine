//
//  IAScrollingData.h
//  MultiTouch
//
//  Created by Konstantin Merker on 26.03.18.
//  Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAScrollingData_h
#define IAScrollingData_h

#include <stdint.h>

typedef struct{
	const IATouch * touch;
	IAArrayList * latestTouches;
	int numLatestTouchesSet;
	void * latestTouchesData;
	float decelerationForScrollingInPixelPerTimeUnitSquared;
} IAScrollingData;


void IAScrollingData_init(IAScrollingData *, float decelerationForScrollingInPixelPerTimeUnitSquared);

void IAScrollingData_startScrolling(IAScrollingData *, const IATouch * touch);

void IAScrollingData_appendNewTouchEvent(IAScrollingData *, float scrollPos, uint64_t time);
void IAScrollingData_removeAllOldTouchEvents(IAScrollingData *, uint64_t time);

void IAScrollingData_endScrolling(IAScrollingData *);

float IAScrollingData_getScrollPosDiffInTimeInterval(IAScrollingData *, uint64_t timeStart, uint64_t timeEnd);

bool IAScrollingData_isScrolling(const IAScrollingData *);
bool IAScrollingData_isCurrentTouch(const IAScrollingData *, const IATouch * touch);

void IAScrollingData_deinit(IAScrollingData *);

#include "IAScrollingData+Generated.h"

#endif
