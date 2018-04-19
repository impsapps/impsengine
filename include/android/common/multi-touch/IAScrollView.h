//
//  IAScrollView.h
//  MultiTouch
//
//  Created by Konstantin Merker on 26.03.18.
//Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAScrollView_h
#define IAScrollView_h

#include <stdint.h>
#include "IARect.h"
#include "IATouchDelegate.h"
#include "IAScrollViewAttributes.h"
#include "IAScrollingData.h"
#include "IAOverscrollingHandler.h"


typedef struct IAScrollView IAScrollView;

struct IAScrollView{
	void * correspondingObject;
	IARect viewPosition;
	float scrollLength;

	IATouchDelegate * touchDelegate;

	uint64_t currentTime;

	IAPoint last;
	uint64_t startTime;
	float startScrollPos;
	//@get
	float currentScrollPos;

	IAScrollingData * scrollingData;
	IAOverscrollingHandler * overscrollingHandler;

	//@get
	bool isScrollable;

	float thresholdInPixelForOnScrollBeginCall;
	bool onScrollBeginCalled;
	void(*onScrollBegin)(void * correspondingObject, IAScrollView * scrollView);
	void(*onScrollEnd)(void * correspondingObject, IAScrollView * scrollView);
	float(*getScrollPosChange)(IAPoint current, IAPoint last);
	uint64_t(*getTime)();
};


void IAScrollView_init(IAScrollView * this, const IAScrollViewAttributes * attr);

bool IAScrollView_isScrolling(const IAScrollView * this);

void IAScrollView_enableScrolling(IAScrollView * this, uint64_t currentTime);
void IAScrollView_updateTime(IAScrollView * this, uint64_t currentTime);
void IAScrollView_disableScrolling(IAScrollView * this, uint64_t currentTime);

float IAScrollView_getOverscrolling(IAScrollView * this);

void IAScrollView_deinit(IAScrollView * this);

#include "IAScrollView+Generated.h"

#endif
