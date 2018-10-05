#include "IALibrary.h"
#include "IAViewHolder.h"
#include "IALogger.h"

#define CLASSNAME "IAViewHolder"


bool IAViewHolder_isSwitchingDone(const IAViewHolder * this, uint64_t currentTime);
void IAViewHolder_finishCurrentSwitch(IAViewHolder * this, uint64_t currentTime);

void IAViewHolder_make(IAViewHolder * this){
    *this = (IAViewHolder){
		.base = IAObject_make(this)
    };
}

IAView * IAViewHolder_getLatestView(const IAViewHolder * this){
    if (this->nextView != NULL) {
        return this->nextView;
    }
    return this->currentView;
}

void IAViewHolder_start(IAViewHolder * this, IAView * view, uint64_t currentTime, const void * viewArgs){
    debugAssert(this->isInsideAnyFunction == false && "Cannot call IAViewHolder_start inside a view delegate call!");
    debugAssert(this->currentView == NULL && "Error in IAViewHolder_start: View holder already started!");
    this->isInsideAnyFunction = true;
    this->currentView = view;
	IAView_setArgs(this->currentView, viewArgs);
    IAView_onFadeInStart(this->currentView, currentTime, 0);
    IAView_onFadeInFinished(this->currentView, currentTime, 0, currentTime);
    this->isInsideAnyFunction = false;
}

void IAViewHolder_switchView(IAViewHolder * this, IAView * nextView, uint64_t currentTime, uint64_t duration, const void * viewArgs){
    debugAssert(this->currentView != nextView && "Error in IAViewHolder_switchView: Switching to same view is not allowed!");
    debugAssert(this->isInsideAnyFunction == false && "Cannot call IAViewHolder_switchView inside a view delegate call!");
    debugAssert(this->currentView != NULL && "Error in IAViewHolder_switchView: View holder not started yet!");
    this->isInsideAnyFunction = true;
    if (IAViewHolder_isSwitching(this)) {
        IAViewHolder_finishCurrentSwitch(this, currentTime);
    }
    this->nextView = nextView;
    this->switchStartTime = currentTime;
    this->switchDuration = duration;
    
    IAView_onFadeOutStart(this->currentView, currentTime, duration);
    IAView_setArgs(this->nextView, viewArgs);
    IAView_onFadeInStart(this->nextView, currentTime, duration);
    if (duration == 0) {
        IAViewHolder_finishCurrentSwitch(this, currentTime);
    }
    this->isInsideAnyFunction = false;
}

bool IAViewHolder_finishCurrentSwitchIfPossible(IAViewHolder * this, uint64_t currentTime){
    debugAssert(this->isInsideAnyFunction == false && "Cannot call IAViewHolder_switchView inside a view delegate call!");
    debugAssert(this->currentView != NULL && "Error in IAViewHolder_switchView: View holder not started yet!");
    if (IAViewHolder_isSwitching(this)) {
        this->isInsideAnyFunction = true;
        IAViewHolder_finishCurrentSwitch(this, currentTime);
        this->isInsideAnyFunction = false;
        return true;
    }else{
        return false;
    }
}

void IAViewHolder_draw(IAViewHolder * this, uint64_t currentTime){
    debugAssert(this->isInsideAnyFunction == false && "Cannot call IAViewHolder_draw inside a view delegate call!");
    debugAssert(this->currentView != NULL && "Error in IAViewHolder_draw: View holder not started yet!");
    this->isInsideAnyFunction = true;
    if (IAViewHolder_isSwitching(this)) {
        if (IAViewHolder_isSwitchingDone(this, currentTime) == false) {
            if (IAView_getZOrder(this->currentView) >= IAView_getZOrder(this->nextView)) {
                IAView_drawFadeIn(this->nextView, this->switchStartTime, this->switchDuration, currentTime);
                IAView_drawFadeOut(this->currentView, this->switchStartTime, this->switchDuration, currentTime);
            }else{
                IAView_drawFadeOut(this->currentView, this->switchStartTime, this->switchDuration, currentTime);
                IAView_drawFadeIn(this->nextView, this->switchStartTime, this->switchDuration, currentTime);
            }
        }else{
            IAViewHolder_finishCurrentSwitch(this, currentTime);
            IAView_draw(this->currentView, currentTime);
        }
    }else{
        IAView_draw(this->currentView, currentTime);
    }
    this->isInsideAnyFunction = false;
}

bool IAViewHolder_isSwitching(const IAViewHolder * this){
    if (this->nextView != NULL) {
        return true;
    }else{
        return false;
    }
}

bool IAViewHolder_isSwitchingDone(const IAViewHolder * this, uint64_t currentTime){
    if (currentTime > this->switchStartTime + this->switchDuration) {
        return true;
    }else{
        return false;
    }
}

void IAViewHolder_stop(IAViewHolder * this, uint64_t currentTime){
    debugAssert(this->isInsideAnyFunction == false && "Cannot call IAViewHolder_stop inside a view delegate call!");
    debugAssert(this->currentView != NULL && "Error in IAViewHolder_stop: View holder not started yet!");
    this->isInsideAnyFunction = true;
    if (IAViewHolder_isSwitching(this)) {
        IAViewHolder_finishCurrentSwitch(this, currentTime);
    }
    IAView_onFadeOutStart(this->currentView, currentTime, 0);
    IAView_onFadeOutFinished(this->currentView, currentTime, 0, currentTime);
    this->currentView = NULL;
    this->isInsideAnyFunction = false;
}

void IAViewHolder_finishCurrentSwitch(IAViewHolder * this, uint64_t currentTime){
    uint64_t finishedTime = this->switchStartTime + this->switchDuration;
    if (currentTime < finishedTime) {
        finishedTime = currentTime;
    }
    IAView_onFadeOutFinished(this->currentView, this->switchStartTime, this->switchDuration, finishedTime);
    IAView_onFadeInFinished(this->nextView, this->switchStartTime, this->switchDuration, finishedTime);
    this->currentView = this->nextView;
    this->nextView = NULL;
}


