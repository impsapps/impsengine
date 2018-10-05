#ifndef IAScrollViewAttributes_h
#define IAScrollViewAttributes_h


#include <stdint.h>
#include "IARect.h"
#include "IAOverscrollingBehavior.h"

typedef struct IAScrollView IAScrollView;


typedef struct{
	//@get
	void * correspondingObject;
	//@set+get
	IARect viewPosition;
	//@set+get
	float scrollLength;

	//@set+get
	float decelerationForScrollingInPixelPerTimeUnitSquared;
	//@set+get
	IAOverscrollingBehavior overscrollingBehavior;

	//@set+get
	float thresholdInPixelForOnScrollBeginCall;
	//@set+get
	void(*onScrollBegin)(void * correspondingObject, IAScrollView * scrollView);
	//@set+get
	void(*onScrollEnd)(void * correspondingObject, IAScrollView * scrollView);
	//@get
	float(*getScrollPosChange)(IAPoint current, IAPoint last);
	//@get
	uint64_t(*getTime)();

	//@set+get
	int zOrder;
} IAScrollViewAttributes;


void IAScrollViewAttributes_makeHorizontal(IAScrollViewAttributes * this, void * correspondingObject, uint64_t(*getTime)());
void IAScrollViewAttributes_makeVertical(IAScrollViewAttributes * this, void * correspondingObject, uint64_t(*getTime)());

#include "IAScrollViewAttributes+Generated.h"

#endif
