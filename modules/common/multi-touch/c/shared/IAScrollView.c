#include "IALibrary.h"
#include "IAScrollView.h"
#include "IATouchDelegate.h"
#include "IATouchManager.h"
#include "IAMath.h"

#define CLASSNAME "IAScrollView"


static void IAScrollView_startScrolling(IAScrollView * this, IATouch touch);
static void IAScrollView_doScroll(IAScrollView * this, IATouch touch);
static void IAScrollView_endCurrentScolling(IAScrollView * this);


static bool IAScrollView_wantToUseTouch(IAScrollView * this, IATouch touch) {
	return IARect_isPointWithin(this->viewPosition, touch.location);
}

static bool IAScrollView_wantToConsumeTouch(IAScrollView * this, IATouch touch) {
	return false;
}

static void IAScrollView_onTouchBegan(IAScrollView * this, size_t numTouches, IATouch touches[numTouches]) {
	for(size_t i = 0; i < numTouches; i++) {
		if (IAScrollView_isScrolling(this)) {
			IAScrollView_endCurrentScolling(this);
		}
		IAScrollView_startScrolling(this, touches[i]);
	}
}

static void IAScrollView_onTouchMoved(IAScrollView * this, size_t numTouches, IATouch touches[numTouches]) {
	for(size_t i = 0; i < numTouches; i++) {
		if (IAScrollingData_isCurrentTouch(this->scrollingData, touches[i])) {
			IAScrollView_doScroll(this, touches[i]);
		}
	}
}

static void IAScrollView_onTouchEnded(IAScrollView * this, size_t numTouches, IATouch touches[numTouches]) {
	for(size_t i = 0; i < numTouches; i++) {
		if (IAScrollingData_isCurrentTouch(this->scrollingData, touches[i])) {
			IAScrollingData_removeAllOldTouchEvents(this->scrollingData, this->getTime());
			IAScrollView_doScroll(this, touches[i]);
			IAScrollView_endCurrentScolling(this);
		}
	}
}

static void IAScrollView_onTouchCanceled(IAScrollView * this) {
    if (IAScrollView_isScrolling(this)) {
        IAScrollingData_removeAllOldTouchEvents(this->scrollingData, this->getTime());
        IAScrollView_endCurrentScolling(this);
    }
}

void IAScrollView_init(IAScrollView * this, const IAScrollViewAttributes * attr) {
	IAOverscrollingBehavior behavior = IAScrollViewAttributes_getOverscrollingBehavior(attr);
	float decelerationForScrollingInPixelPerTimeUnitSquared = IAScrollViewAttributes_getDecelerationForScrollingInPixelPerTimeUnitSquared(attr);

	*this = (IAScrollView) {
        .base = IAObject_make(this),
		.correspondingObject = IAScrollViewAttributes_getCorrespondingObject(attr),
		.viewPosition = IAScrollViewAttributes_getViewPosition(attr),
		.scrollLength = IAScrollViewAttributes_getScrollLength(attr),
		.scrollingData = IAScrollingData_new(decelerationForScrollingInPixelPerTimeUnitSquared),
		.overscrollingHandler = IAOverscrollingHandler_new(behavior),
		.thresholdInPixelForOnScrollBeginCall = IAScrollViewAttributes_getThresholdInPixelForOnScrollBeginCall(attr),
		.onScrollBegin = IAScrollViewAttributes_getOnScrollBeginFunction(attr),
		.onScrollEnd = IAScrollViewAttributes_getOnScrollEndFunction(attr),
		.getScrollPosChange = IAScrollViewAttributes_getGetScrollPosChangeFunction(attr),
		.getTime = IAScrollViewAttributes_getGetTimeFunction(attr)
	};

	IATouchDelegateAttributes touchDelegateAttr;
	IATouchDelegateAttributes_make(&touchDelegateAttr, this);
	IATouchDelegateAttributes_setWantToUseTouchFunction(&touchDelegateAttr, (bool(*)(void *, IATouch)) IAScrollView_wantToUseTouch);
	IATouchDelegateAttributes_setWantToConsumeTouchFunction(&touchDelegateAttr, (bool(*)(void *, IATouch)) IAScrollView_wantToConsumeTouch);
	IATouchDelegateAttributes_setOnTouchBeganFunction(&touchDelegateAttr, (void(*)(void *, size_t, IATouch[])) IAScrollView_onTouchBegan);
	IATouchDelegateAttributes_setOnTouchMovedFunction(&touchDelegateAttr, (void(*)(void *, size_t, IATouch[])) IAScrollView_onTouchMoved);
	IATouchDelegateAttributes_setOnTouchEndedFunction(&touchDelegateAttr, (void(*)(void *, size_t, IATouch[])) IAScrollView_onTouchEnded);
    IATouchDelegateAttributes_setOnTouchCanceledFunction(&touchDelegateAttr, (void(*)(void *)) IAScrollView_onTouchCanceled);
	IATouchDelegateAttributes_setZOrder(&touchDelegateAttr, IAScrollViewAttributes_getZOrder(attr));
    IATouchDelegate_init(&this->touchDelegate, &touchDelegateAttr);
	IA_incrementInitCount();
}

bool IAScrollView_isScrolling(const IAScrollView * this) {
	return IAScrollingData_isScrolling(this->scrollingData);
}

static void IAScrollView_startScrolling(IAScrollView * this, IATouch touch) {
	debugAssert(IAScrollView_isScrolling(this) == false);
	this->startTime = this->getTime();
	this->startScrollPos = this->currentScrollPos;
	this->last = touch.location;
	IAScrollingData_startScrolling(this->scrollingData, touch);
	IAScrollingData_appendNewTouchEvent(this->scrollingData, this->currentScrollPos, this->startTime);
}

static void IAScrollView_doScroll(IAScrollView * this, IATouch touch) {
	IAPoint current = touch.location;
	float scrollPosChange = this->getScrollPosChange(current, this->last);
	IAOverscrollingHandler_modifyCurrentDragLengthIfNeeded(this->overscrollingHandler, &scrollPosChange);
	this->last = current;

	this->currentScrollPos += scrollPosChange;
	if (this->currentScrollPos > this->scrollLength) {
		scrollPosChange = this->currentScrollPos - this->scrollLength;
		this->currentScrollPos = this->scrollLength;
	} else if (this->currentScrollPos < 0.0f)  {
		scrollPosChange = this->currentScrollPos;
		this->currentScrollPos = 0.0f;
	} else {
		scrollPosChange = 0.0f;
	}

	IAOverscrollingHandler_appendDragLength(this->overscrollingHandler, scrollPosChange);

	IAScrollingData_appendNewTouchEvent(this->scrollingData, this->currentScrollPos, this->getTime());

	if (this->onScrollBeginCalled == false &&
		fabsf(this->currentScrollPos - this->startScrollPos) > this->thresholdInPixelForOnScrollBeginCall) {
		this->onScrollBeginCalled = true;
		if (this->onScrollBegin) {
			this->onScrollBegin(this->correspondingObject, this);
		}
	}
}

static void IAScrollView_endCurrentScolling(IAScrollView * this) {
	debugAssert(IAScrollView_isScrolling(this));

	IAScrollingData_endScrolling(this->scrollingData);

	if (this->onScrollBeginCalled) {
		this->onScrollBeginCalled = false;
		if (this->onScrollEnd) {
			this->onScrollEnd(this->correspondingObject, this);
		}
	}
	this->startTime = this->getTime();
	this->currentTime = this->startTime;
	this->startScrollPos = this->currentScrollPos;
}

void IAScrollView_enableScrolling(IAScrollView * this, uint64_t currentTime) {
	debugAssert(IAScrollView_isScrollable(this) == false);
	IATouchManager_registerTouchDelegate(&this->touchDelegate);
	this->currentTime = currentTime;
}

void IAScrollView_updateTime(IAScrollView * this, uint64_t currentTime) {
	if (IAScrollView_isScrolling(this) == false) {
		IAOverscrollingHandler_scrollBack(this->overscrollingHandler, currentTime - this->currentTime);
		float scrollPosDiff = IAScrollingData_getScrollPosDiffInTimeInterval(this->scrollingData, this->currentTime, currentTime);
		this->currentScrollPos += scrollPosDiff;
		if (this->currentScrollPos > this->scrollLength) {
			this->currentScrollPos = this->scrollLength;
		} else if (this->currentScrollPos < 0.0f) {
			this->currentScrollPos = 0.0f;
		}
		this->currentTime = currentTime;
	}
}

void IAScrollView_disableScrolling(IAScrollView * this, uint64_t currentTime) {
	debugAssert(IAScrollView_isScrollable(this) == true);
	IAScrollView_updateTime(this, currentTime);
	IATouchManager_unregisterTouchDelegate(&this->touchDelegate);
}

float IAScrollView_getOverscrolling(IAScrollView * this) {
	return IAOverscrollingHandler_getAdditionalOffset(this->overscrollingHandler);
}

void IAScrollView_deinit(IAScrollView * this) {
	IAScrollingData_release(this->scrollingData);
	IAOverscrollingHandler_release(this->overscrollingHandler);
	IATouchDelegate_deinit(&this->touchDelegate);
	IA_decrementInitCount();
}

